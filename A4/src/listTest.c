/*Justin Carvalho*/
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "linkedList.h"

//error codes
#define STRUCTFAILURE 1
#define LISTFAILURE 2
#define MEMERROR 10
#define OTHER 11

Food* createRecord_basicTest();
void printRecord_basicTest(Food* p);
bool length_test(Food* head, int expectedLength);
Food* addToFront_basicTest(Food* record);
Food* addToBack_basicTest(Food* head, int expectedLength);
void getLastItem_fullTest(Food* head);
Food* removeFromFront_fullTest(Food* head);
Food* removeFromBack_fullTest(Food* head);
void isEmpty_basicTest(Food* head);
void removes_emptyTest();
void isEmpty_basicTest(Food* head);

void segfault_sigaction(int signal, siginfo_t *si, void *arg);

#define CSVLENGTH 12
void mark(int n);
void printMark();
int csv[50];
int csv_i=0;

int main() {
    Food* head = NULL;
    struct sigaction sa;

    /*segfault catcher*/
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    printf("structTest begin\n");
    head = createRecord_basicTest();
    if (!head) {
        printf("X STRUCTFAILURE: Did not return a struct in createRecord_basicTest -> cannot continue\n");
        mark(0);
        printMark();
        exit(STRUCTFAILURE);
    } else {
        printf("  STRUCTPASS: Returned a struct in createRecord_basicTest\n");
        mark(1);
    }

    printRecord_basicTest(head);
    printf("structTest end\n\n");

    printf("listTest begin\n");

    head = addToFront_basicTest(head);
    if (!head) {
        printf("X LIST FAILURE: did not return a list in addToFront_basicTest -> cannot continue\n");
        mark(0);
        printMark();
        exit(LISTFAILURE);
    } else {
        printf("  LIST PASS: continuing...\n");
        mark(1);
    }

    if (! length_test(head, 2)) {
        printf("X LIST FAILURE: List structure is broken -> cannot continue\n");
        mark(0);
        printMark();
        exit(LISTFAILURE);
    } else {
        printf("  LIST PASS: continuing...\n");
        mark(1);
    }

    head = addToBack_basicTest(head, 3);
    if (!head) {
        printf("X LIST FAILURE: did not return a list in addToFront_basicTest -> cannot continue\n");
        mark(0);
        printMark();
        exit(LISTFAILURE);
    } else {
        printf("  LIST PASS: continuing...\n");
        mark(1);
    }

    getLastItem_fullTest(head);

    head = removeFromFront_fullTest(head);
    if (!head) {
        printf("     LISTFAILURE: removeFromFront failed test -> cannot continue\n");
        mark(0);
        printMark();
        exit(LISTFAILURE);
    } else {
        printf("  LIST PASS: continuing...\n");
        mark(1);
    }

    head = removeFromBack_fullTest(head);
    if (!head) {
        printf("     LISTFAILURE: removeFromBack failed test -> cannot continue\n");
        mark(0);
        printMark();
        exit(LISTFAILURE);
    } else {
        mark(1);
    }
    isEmpty_basicTest(head);
    removes_emptyTest();
    printf("listTest end\n");

    printf("\nCompleted all tests\n");
    printf("This version didn't test: printList, destroyList, destroyRecord\n");
    printf("You must test these yourself\n");

    printMark();
    return 0;
}

Food* createRecord_basicTest() {
    char* name;
    char* group;
    Food* item;
    printf("  Begin createRecord_basicTest\n");

    name = malloc(sizeof(char) * 3);
    if (!name) {
        printf("!TESTERROR: malloc failed\n");
        return NULL;
    }
    group = malloc(sizeof(char) * 4);
    if (!group) {
        printf("!TESTERROR: malloc failed\n");
        free(name);
        return NULL;
    }

    strcpy(name, "pi");
    strcpy(group, "fat");

    printf("    calling createRecord(pi, fat, 1.1, j");
    item = createRecord(name, group, 1.1, 'j');
    if (!item) {
        printf("X    STRUCTFAILURE: createRecord() returned an unexpected NULL\n");
        printf("    either malloc failed (unlikely), or you did something really wrong\n");
        return NULL;
    }

    printf("     createRecord return value? YES\n");

    printf("     name == struct->name? %s",
        (strcmp(name, item->name)) ? "NO" : "YES");
    printf("     foodGroup == struct->foodGroup? %s\n",
        (strcmp(group, item->foodGroup)) ? "NO" : "YES");
    printf("     calories == struct->calories? %s\n",
        (((double)1.1) == item->calories) ? "YES" : "NO");
    printf("     type == struct->type? %s\n",
        ('j' == item->type) ? "YES" : "NO");

    free(name);
    free(group);
    name = group = NULL;

    printf("    If you segfault during the next test, you didn't copy the string to new memory.\n");

    item->name[1] = 'a';
    item->foodGroup[2] = 'a';

    if (item->name[1] == 'a'
        && item->foodGroup[2] == 'a') {
        printf("    Use your own memory? YES\n");
    } else {
        printf("    Use your own memory? NO\n");
    }

    item->name[1] = 'i';
    item->foodGroup[2] = 't';
    printf(" End createRecord_basicTest\n");

    return item;
}

void printRecord_basicTest(Food* p) {
    char* rStr = NULL; //returned string
    char tStr[150] = "pi (fat):1.10[j]"; //test string
    int sigh=0; //prevents infinte loop is failed to nullTerminate
    int error=0;
    printf("  Begin printRecord_basicTest\n");
    printf("    ASSUMES: createRecord is correct\n");

    rStr = printRecord(p);
    if (!rStr) {
        printf("X    STRUCTFAILURE: printRecord() returned an unexpected NULL\n");
        printf("    either malloc failed (unlikely), or you did something really wrong\n");
        return;
    }

    printf("    printRecord return value? YES\n");
    printf("    checking for match to '%s'\n", tStr);
    while (rStr[sigh] != '\0') {
        if (rStr[sigh] != tStr[sigh]) {
            printf("X   STRUCTFAILURE: string differs at index %d\n", sigh);
            error++;
        }
        sigh++;
    }

    if (!error) {
        printf("    testString:     '%s'\n", tStr);
        printf("    returnedString: '%s'\n", rStr);
        printf("  STRUCTPASS: printRecord_basicTest looks good\n");
        mark(1);
    } else {
        mark(0);
    }

    free(rStr);
    printf("  End printRecord_basicTest\n");
}

bool length_test(Food* head, int expectedLength) {
    Food* i;
    int length = 0;
    printf("  begin length_test\n");
    printf("    This test ensures the integrity of your linked list\n");
    printf("    A segfault here means something is wrong with struct->next\n");

    if (head == NULL) {
        printf("!TESTERROR: head was NULL in length_test\n");
        return false;
    }

    for (i=head; i!=NULL; i=i->next) {
        length++;
    }

    printf("    Does length(%d) = expected(%d)? ", length, expectedLength);
    if (length == expectedLength) {
        printf("YES\n");
        printf("  end length_test\n");
        return true;
    } else {
        printf("NO\n");
        printf("  end length_test\n");
        return false;
    }
}

Food* addToFront_basicTest(Food* record) {
    Food* head = NULL;
    Food* headRecord = NULL;
    printf(" addToFront_basicTest begin\n");
    printf("     ASSUMES: createRecord is correct\n");

    headRecord = createRecord("Apple", "vegfruit", 3.16, 'h');
    if (!headRecord) {
        printf("    STRUCTERROR: createRecord returned an unexpected NULL\n");
        return NULL;
    }

    head = addToFront(record, headRecord);
    if (!head) {
        printf("     LISTERROR: addToFront returned an unexpected NULL\n");
        return NULL;
    }
    if (head->name == NULL || head->foodGroup == NULL) {
        printf("     LISTERROR: addToFront nulled struct->title and struct->artist\n");
        return NULL;
    }

    printf("     AddToFront returns the head(front) of list as defined by spec\n");
    printf("     Expecting \"%s (%s)\" at memory address %p at the head(front) of list\n",
        headRecord->name, headRecord->foodGroup, (void*)headRecord);
    printf("     Yours returned \"%s (%s)\" at memory address %p\n", head->name, head->foodGroup, (void*)head);
    printf("     Does & == & ? %s\n", (headRecord == head) ? "YES" : "NO");
    printf(" addToFront_basicTest end\n");

    return head;
}

Food* addToBack_basicTest(Food* head, int expectedLength) {
    int length=0;
    Food* i = NULL;
    Food* back = NULL;
    Food* newHead = NULL;
    printf(" begin addToBack_basicTest\n");
    printf("    ASSUMES: createRecord is correct, and list structure is valid\n");

    back = createRecord("Cake", "fat", 2.7, 'j');
    if (!back) {
        printf("    STRUCTERROR: createRecord returned an unexpected NULL\n");
        return NULL;
    }

    printf("     calling addToBack\n");

    newHead = addToBack(head, back);
    if (!newHead) {
        printf("     LISTERROR: addToFront returned an unexpected NULL\n");
        return NULL;
    }

    printf("     AddToBack returns the head(front) of list as defined by spec\n");
    printf("     Expecting \"%s (%s)\" at memory address %p at the head(front) of list\n",
        head->name, head->foodGroup, (void*)head);
    printf("     Yours returned \"%s (%s)\" at memory address %p\n", newHead->name, newHead->foodGroup, (void*)newHead);
    printf("     Does & == & ? ");
    if (newHead == head) {
        printf("YES\n");
    } else {
        printf("NO\n");
        printf("     !LISTERROR: addToBack compromises list integrity by dirtying the head\n");
        return NULL;
    }

    for (i=head; i->next!=NULL; i=i->next) {
        length++;
    }
    length++;
    if (length != expectedLength) {
        printf("     LISTERROR: addToBack broken the structure of your list\n");
        printf("        Check struct->next\n");
        return NULL;
    }

    printf("     Expecting \"%s (%s)\" at memory address %p at the back of list\n",
        back->name, back->foodGroup, (void*)back);
    printf("     Yours returned \"%s (%s)\" at memory address %p\n", i->name, i->foodGroup, (void*)i);
    printf("     Does & == & ? ");
    if (back == i) {
        printf("YES\n");
    } else {
        printf("NO\n");
        printf("     !LISTERROR: addToBack didn't add my pointer to the back\n");
        return NULL;
    }
    printf(" end addToBack_basicTest\n");

    return newHead;
}

void getLastItem_fullTest(Food* head) {
    Food* end;
    printf(" begin getLastItem_fullTest\n");
    printf("     calling getLastItem\n");
    end = getLastItem(head);
    if (!end) {
        printf("     LISTERROR: getLastItem returned unexpected NULL\n");
        return;
    }
    printf("     Does last item = Cake (fat) ? ");
    if (strcmp(end->name, "Cake") == 0) {
        printf("YES\n");
        mark(1);
    } else {
        printf("NO\n");
        printf("     LISTERROR: getLastItem didn't return last item\n");
        mark(0);
    }
    printf(" end getLastItem_fullTest\n");
}

Food* removeFromFront_fullTest(Food* head) {
    Food* newhead;
    printf(" begin removeFromFront_fullTest\n");
    printf("     Current List: apple, pi, cake\n");
    printf("     calling removeFromFront\n");
    newhead = removeFromFront(head);
    if (!newhead) {
        printf("     LISTERROR: removeFromFront returned an unexpected NULL\n");
        return NULL;
    }
    printf("     Expecting new head == pi ? ");
    if (strcmp(newhead->name, "pi") == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
        printf("     LISTERROR: Didn't return the correct head\n");
        printf("      You returned %s\n", newhead->name);
        return NULL;
    }
    printf(" end removeFromFront_fullTest\n");
    free(head);
    return newhead;
}

Food* removeFromBack_fullTest(Food* head) {
    Food* newHead;
    printf(" begin removeFromBack_fullTest\n");
    printf("     Current List: pi, cake\n");
    printf("     calling removeFromBack\n");
    newHead = removeFromBack(head);
    if (!newHead) {
        printf("     LISTERROR: removeFromBack returned an unexpected NULL\n");
        return NULL;
    }
    printf("     Returned pi? ");
    if (strcmp(newHead->name, "pi") == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
        printf("     LISTERROR: Didn't return the correct struct back\n");
        printf("      You returned %s\n", newHead->name);
        return NULL;
    }
    printf("     Checking list structure, does length == 1 ? ");
    if (head->next == NULL) {
        printf("YES\n");
    } else {
        printf("NO\n");
        printf("      LISTERROR: Length isn't 1\n");
        printf("      Make sure you set endoflist->next to null\n");
        return NULL;
    }
    printf(" end removeFromBack_fullTest\n");
    return newHead;
}

void isEmpty_basicTest(Food* head) {
    printf(" begin isEmptyTest\n");
    printf("     Is not empty? ");
    if (! isEmpty(head)) {
        printf("YES\n");
        mark(1);
    }  else {
        printf("NO\n");
        printf("     LISTERROR: List should be reported not empty\n");
        printf("     Check for not NULL\n");
        mark(0);
    }
    printf("     Emptying list...\n");
    free(head);
    head = NULL;
    printf("     Is empty? ");
    if (isEmpty(head)) {
        printf("YES\n");
        mark(1);
    }  else {
        printf("NO\n");
        printf("     LISTERROR: List should be reported empty\n");
        printf("     Check for NULL\n");
        mark(0);
    }
    printf(" end isEmptyTest\n");
}

void removes_emptyTest() {
    printf(" begin removeFrom____emptyTest\n");
    printf("     Does removeFromFront return NULL? ");
    if (! removeFromFront(NULL)) {
        printf("YES\n");
        mark(1);
    }  else {
        printf("NO\n");
        printf("      LISTERROR: removeFromFront should return NULL\n");
        printf("      Check for NULL\n");
        mark(0);
    }
    printf("     Does removeFromBack return NULL? ");
    if (! removeFromBack(NULL)) {
        printf("YES\n");
        mark(1);
    }  else {
        printf("NO\n");
        printf("      LISTERROR: removeFromBack should return NULL\n");
        printf("      Check for NULL\n");
        mark(0);
    }
    printf(" end removeFrom____emptyTest\n");
}

void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
    printf("\nX  Caught segfault at address %p\n", si->si_addr);
    printMark();
    exit(0);
}

void mark(int n) {
    csv[csv_i] = n;
    csv_i++;
}

void printMark() {
    int i, diff;
    printf("\n\n*********************************\n");

    printf("@List test grade:\n");
    for (i=0; i<(csv_i - 1); i++) {
        printf("%d, ", csv[i]);
    }
    printf("%d", csv[i]);

    diff = CSVLENGTH - i - 1;
    for (i=0; i<diff; i++) {
        printf(", 0");
    }

    printf("\n");
}
