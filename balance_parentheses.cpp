#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;
/*
    Submitted by Usman Ayobami
 */
class node
{
public:
    node *next, *prev;
    char ID;
    node(char ID)
    {
        next = nullptr;
        prev = nullptr;
        this->ID = ID;
    }
};

class linked_list
{
public:
    node *head, *tail;
    char nodes, max_nodes;

    linked_list(char maxNodes)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->nodes = 0;
        this->max_nodes = maxNodes;
    }

    char size()
    {
        return nodes;
    }
    bool empty()
    {
        return size() <= 0;
    }
    bool full()
    {
        return size() >= max_nodes;
    }
    void insert_tail(node *new_node)
    {
        if (empty())
        {
            head = new_node;
            tail = new_node;
            nodes = nodes + 1;
        }
        else if (full())
        {
            cout << "An attempt to insert was made while Linked List is full";
        }
        else
        {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
            nodes = nodes + 1;
        }
    };
    void delete_tail()
    {
        if (empty())
        {
            cout << "An attempt to delete was made while Linked List is empty";
        }
        if (size() == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            nodes = nodes - 1;
        }
        else
        {
            tail = tail->prev;
            tail->next->prev = nullptr;
            delete tail->next;
            tail->next = nullptr;
            nodes = nodes - 1;
        }
    }
    void insert_head(node *new_node)
    {
        if (empty())
        {
            head = new_node;
            tail = new_node;
            nodes = nodes + 1;
        }
        else if (full())
        {
            cout << "An attempt to insert was made while Linked List is full";
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            nodes = nodes + 1;
        }
    };

    void delete_head()
    {
        if (empty())
        {
            cout << "An attempt to delete was made while Linked List is empty";
        }
        if (size() == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            nodes = nodes - 1;
        }
        else
        {
            head = head->next;
            head->prev->next = nullptr;
            delete head->prev;
            head->prev = nullptr;
            nodes = nodes - 1;
        }
    }
};

class mystack
{
public:
    linked_list *LL;
    mystack(char max_nodes)
    {
        if (max_nodes > 0)
            LL = new linked_list(max_nodes);
        else
            LL = nullptr;
    };
    // push item onto stack
    void push(char new_node)
    {
        node *newNode = new node(new_node);
        LL->insert_tail(newNode);
    };
    // pops item from top of stack
    char pop()
    {
        char newID = LL->tail->ID;
        LL->delete_tail();
        return newID;
    };
    // returns Boolean of whether stack is currently empty
    bool isEmpty()
    {
        return LL == nullptr || LL->empty();
    }
    // returns Boolean of whether stack is currently full
    bool isFull()
    {
        return LL != nullptr && LL->full();
    }
    // clears the stack
    void clear()
    {
        if (LL != nullptr)
        {
            while (!LL->empty())
            {
                LL->delete_tail();
            }
        }
    }
    // looks at the top item of the stack without removing it
    char peek()
    {
        if (LL != nullptr && !LL->empty())
        {
            return LL->tail->ID;
        }
        else
        {
            cout << "An attempt to peek was made while stack is empty";
            return -1;
        }
    }
};

class myqueue
{
public:
    linked_list *LL;
    myqueue(int max_nodes)
    {
        if (max_nodes > 0)
            LL = new linked_list(max_nodes);
        else
            LL = nullptr;
    };
    // adds item to front of queue
    void enqueue(node *new_node)
    {
        LL->insert_tail(new_node);
    };
    // removes item from rear of queue
    node *dequeue()
    {
        if (!isEmpty())
        {
            node *removedNode = LL->head;
            LL->delete_head();
            return removedNode;
        }
        else
        {
            return nullptr;
        }
    }
    // returns Boolean of whether queue is currently empty
    bool isEmpty()
    {
        return LL != nullptr && LL->empty();
    }
    // returns Boolean of whether queue is currently full
    bool isFull()
    {
        return LL != nullptr && LL->full();
    }
    // clears the queue
    void clear()
    {
        if (LL != nullptr)
        {
            while (!LL->empty())
            {
                LL->delete_head();
            }
        }
    }
    // looks at the item at the end of the queue without removing it
    char poll()
    {
        if (LL != nullptr && !LL->empty())
        {
            return LL->head->ID;
        }
        else
        {
            cout << "An attempt to poll was made while queue is empty";
            return -1;
        }
    }
};

class StackParenthesesChecker
{
public:
    /*
    Returns Boolean of whether the string input has balanced parentheses.

    The idea is to iterate through the string input and put all opening parentheses in the stack,
    when i hit a closing parentheses, I will check if the stack is not empty and the tail of the stack
    is an opening parentheses, then pop the stack and coninue the iteration. If at the end of the iteration,
    the stack is empty, that means all parentheses are balanced.
     */
    bool isBalanced(string input)
    {
        mystack s(input.length()); // Setting the max_nodes of the stack as the lenght of the input string
        // iterate through the string input
        for (char c : input)
        {
            if (c == '(')
            {
                // put all opening parentheses in the stack
                s.push(c);
            }
            else if (c == ')')
            {
                // If there's an opening parenthesis on the stack, pop it
                if (!s.isEmpty() && s.peek() == '(')
                {
                    s.pop();
                }
                else
                {
                    // Unmatched closing parenthesis
                    return false;
                }
            }
            else
            {
                // Handle characters other than '(' and ')'
                cout << "Error: Invalid character '" << c << "'" << endl;
                return false;
            }
        }
        // If the stack is empty, all parentheses are balanced
        return s.isEmpty();
    }
};

class QueueParenthesesChecker
{
public:
    /*
    Returns Boolean of whether the string input has balanced parentheses.

    The idea:
    Create two queues; q1 and q2, one for "(" and the other for ")"
    Iterate through the string input
    for all character in string input:
        If I encounter "(",
            enqueue q1.
        If I encounter ")",
            if q1 is empty
                return false [i.e Mismatched closing parenthesis]
            else enqueue q2 [this is the end of a matching parentheses]
    for each ")" in q2
        dequeue q1 and q2
    After iterating through the entire string input,
    If q1 and q2 are empty, that means the string is balanced
      */
    bool isBalanced(string input)
    {
        myqueue queue1(input.length()); // Setting the max_nodes of the queue as the lenght of the input string
        myqueue queue2(input.length()); // Setting the max_nodes of the queue as the lenght of the input string

        // iterate through the string input
        for (char c : input)
        {
            if (c == '(')
            {
                // enqueue q1
                queue1.enqueue(new node(c));
            }
            else if (c == ')')
            {
                if (queue1.isEmpty()) // Mismatched closing parenthesis
                {
                    return false;
                }
                else
                {
                    // enqueue q2
                    queue2.enqueue(new node(c));
                }
            }
        }

        // Check if the number of '(' and ')' parentheses matches
        while (!queue2.isEmpty())
        {
            if (!queue1.isEmpty() && queue1.poll() == '(')
            {
                queue1.dequeue();
                queue2.dequeue();
            }
            else
            {
                return false;
            }
        }
        // If there's any unmatched opening parenthesis or mismatched count, return false
        if (!queue1.isEmpty())
        {
            return false;
        }
        // If both queues are empty, parentheses are balanced
        return queue2.isEmpty();
    }
};
int main()
{
    StackParenthesesChecker stack_checker;
    QueueParenthesesChecker queue_checker;

    string input;
    while (true)
    {
        cout << "Enter a string (or 'quit' to exit): ";
        getline(cin, input);
        if (input == "quit")
        {
            break;
        }
        if (stack_checker.isBalanced(input) && queue_checker.isBalanced(input))
        {
            cout << "The input string " << input << " has balanced parentheses." << endl;
        }
        else
        {
            cout << "The input string " << input << " does not have balanced parentheses." << endl;
        }
    }
    return 0;
}