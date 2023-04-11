#include<iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <conio.h>
#include<windows.h>
using namespace std;

class node
{
public:
    string data;
    node *left, *right;
    int rim=0;
    node(string d)
    {
        data=d;
        left=right=NULL;
    }
};

class BST
{
public:
    node *create(string d, node *r)
    {
        int ASCII=d[0];
        if(r==NULL)
        {
            r=new node(d);
        }

        else if(ASCII>r->data[0]){
            r->right=create(d,r->right);
        }
        else{
            r->left=create(d,r->left);
        }
        return r;
    }


    int sp=0;
    void inorder(node *r)
    {
        if(r!=NULL)
        {
            inorder(r->left);
            cout<< r->data<< "   " ;
            inorder(r->right);

            sp++;
            if(sp%10==0)
            {
                cout<< endl;
            }
        }

    }

    node *Search(string i,node *r)
    {


        if(r==NULL || r->data==i)
        {
            return r;
        }
        if(r->data[0]<i[0])
        {
            return Search(i,r->right);
        }
        else
        {
            return Search(i,r->left);
        }
    }


    node *Min(node *r)
    {
        if(r->left==NULL)
        {
            return r;
        }
        return Min(r->left);
    }

    node *Delete(node *r,string d)
    {
        if(r==NULL)
        {
            return r;
        }
        if(d<r->data)
            {
                r->left=Delete(r->left,d);
            }
        else if(d>r->data)
            {
                r->right=Delete(r->right,d);
            }
        else{
                if(r->left==NULL && r->right==NULL)
                {
                    node *t=r;
                    r=NULL;
                    delete t;
                    return r;
                }
                else if(r->left==NULL)
                {
                    node *t=r;
                    r=r->right;
                    delete t;
                    return r;

                }
                else if(r->right==NULL)
                {
                    node *t=r;
                    r=r->left;
                    delete t;
                    return r;
                }
                else if(r->left!=NULL && r->right!=NULL){
                    node *temp=Min(r->right);
                    r->data=temp->data;
                    r->right=Delete(r->right,temp->data);

                }
            }
            return r;
    }

};

void menu()
{
    getch();
    cout<< "\n\n\n\n1. Insert a new word.\n";
    cout<< "2. Traverse hole dictionary in Inorder.\n";
    cout<< "3. Search Operation.\n";
    cout<< "4. Deletion Operation.\n";
    cout<< "5. Advance Search Operation.\n";
    cout<< "6. Find similar.\n";
    cout<< "7. Exit the proggram.\n";


}

int main()
{
//    colour(5f);
    node *root=NULL;
    BST *ob=new BST();


    // Combination of file in BST
    ofstream file1;
    file1.open("D.txt",ios::out|ios::app);
    file1.close();
    ifstream file("D.txt");
    string mainWord;
    string Mining;
    int c=0;
    while(getline(file,mainWord))
    {
        c++;
        if(c%2!=0)
        {
            root=ob->create(mainWord,root);
        }
    }

    file.close();
    // file closed ......!


    ofstream fileRev; // opening reverse file.
    fileRev.open("RD.txt",ios::out|ios::app);
    fileRev.close();


    while(1){
    menu();
    cout<< "\nEnter your choice: ";
    int n;
    cin>>n;
    if(n==1)
    {

        cout<< "Enter a new word: ";
        string word;
        getline(cin>> ws,word);
        root=ob->create(word,root);


        cout<< "\nEnter the meaning of this word: \n";
        string mining;
        getline(cin>> ws,mining);

        ofstream file2;
        file2.open("D.txt",ios::out|ios::app);
        file2<<endl<< word <<endl <<  mining;
        file2.close();


        ofstream ReverseFile; // inserting the new word in Reverse file
        ReverseFile.open("RD.txt",ios::out|ios::app);
        ReverseFile<<endl<< mining <<endl << word ;
        ReverseFile.close();
        cout<< "\n......... The Word is Inserted..........!";


    }

    else if(n==2)
    {
        cout<< "\n\nTraverse in Inorder: \n";
    ob->inorder(root);
    cout<<endl;
    }


    else if(n==3)
    {
        cout<< "Enter a word to search in dictionary: ";
        string p;
        getline(cin>> ws,p);

        if(ob->Search(p,root)==NULL)
        {
            cout<< "\nThe word is not found....!\n";
        }

        else{
        ifstream fileSearch("D.txt");
        c=0;
        int r=0;

        while(getline(fileSearch,mainWord))
        {
            c++;
            if(r!=0)
            {
                cout<< "Meaning of this word is :->  "<< mainWord<<endl;
                break;
            }
            if(c%2!=0)
            {
                if(mainWord==p)
                {
                    cout<< "\nThe word is found....!\n";
                    r=c;
                }
            }

        }
            fileSearch.close();

        }

    }

    else if(n==4)
    {
        node *r=NULL;
        cout<< "Enter a word to delete: ";
        string d;
        getline(cin>> ws,d);
        if(ob->Search(d,root)==NULL)
        {
            cout<< "\nThe word is not found in the dictionary....!\n";
        }
        else{
        r=ob->Delete(root,d);
        cout<< d<< " is deleted......!";
        }
    }

    else if(n==5)
    {
        cout<< "Enter a word to search in dictionary: ";
        string s;
        getline(cin>> ws,s);

        if(ob->Search(s,root)==NULL)
        {
            cout<< "\nThe word is not found....!\n";

            cout<< "Do you mean:  ";
            string mean;
            ifstream file3("D.txt");
            while(getline(file3,mean))
            {
                  if(mean[0]==s[0] && mean[1]==s[1] && mean[2]==s[2])
                  {
                      cout<< mean<< "   ";
                  }
            }

            file3.close();

        }
        else{

            cout<< "\nThe word is found....!\n";

            ifstream fileSame("Reverse Dictionary file.txt");



        }

    }

    else if(n==6)
    {
        cout<< "Enter a word to find the similar meaning word in dictionary: ";
        string p;
        getline(cin>> ws,p);
        if(ob->Search(p,root)==NULL)
        {
            cout<< "\nThe word is not found....!\n";

        }
        else{

            cout<< "\nThe word is found....!\n";
            string Word;
            string storMean;
            c=0;
            ifstream findMean("D.txt");
            while(getline(findMean,Word))
            {
                if(c==1)
                {
                    storMean=Word;
                    c=0;
                }

                if(Word==p)
                {
                    c++;
                }
            }

            cout << "The meaning of this word: "<< storMean<< endl;

            ifstream fileSame("RD.txt");
            string mean;
            c=0;
            int r=0;
            cout<< "The similar meaning words: ";
            while(getline(fileSame,Word))
            {
                if(c==1)
                {
                    cout<< Word <<"    ";
                    c=0;
                }

                if(storMean==Word)
                {
                    c++;
                    r++;
                }
            }

            if(r==0)
            {
                cout<< "There is no similar meaning words.";
            }

        }
    }

    else if(n==7)
    {
        return 0;
    }


    }

}



