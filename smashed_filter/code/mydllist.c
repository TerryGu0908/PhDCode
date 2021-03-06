//Doubly linked list implementation
struct Node {
  char data[20];
  struct Node* next;
  struct Node* prev;
};

struct Node* sentinel; //global pointer to the sentinel node
struct Node* head;
struct Node* tail;

// Create sentinel node, originally it just points to itself

struct Node* MakeSentinel () {
  struct Node* SentinelNode = (struct Node*)malloc(sizeof(struct Node));
  SentinelNode->next = SentinelNode->next;
  SentinelNode->prev = SentinelNode->prev;
  return SentinelNode;
}

//Creation of a node takes an int and returns a node
struct Node* GetNewNode (char *x) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); //created node in the dynamic memory
    strcpy (newNode->data, x); //temp->data is same as (*temp).data
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

//Returning a pointer to newly created node, inserts next to sentinel
void InsertAtHead (char *x){
    struct Node* newNode = GetNewNode(x);
    if (sentinel == NULL) {
      sentinel = MakeSentinel();
      head = newNode;
      sentinel->next = head;
      sentinel->prev = head;
      head->next = sentinel;
      head->prev = sentinel;
      return;
    }

 head->prev = newNode;
 newNode->next = head;
 newNode->prev = sentinel;
 sentinel->prev = newNode;
 head = newNode;
}

void PrintHead() {
//    printf("Sentinel prev is %s\n", sentinel->prev->data);
  struct Node* temp = sentinel->prev;
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("The players in the game are\n\n");
  while (temp != sentinel) {
    printf ("%s ", temp->data);
    temp = temp->next;

  }
  printf("\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

//Removing a name from the linked list
void DeleteEntry (struct Node* del) {
    if ((del->next != sentinel) && (del->prev != sentinel)) {
      del->next->prev = del->prev;
      del->prev->next = del->next;
    }
    else if (del->next == sentinel) {
      del->next->next = del->prev;
      del->prev->next = del->next;
    }
    else if(del->prev == sentinel) {
      del->next->prev = del->prev;
      del->prev->prev = del->next;
    }
    //    printf("Sentinel prev is now%s\n", sentinel->prev->data);
    
    return;
}
