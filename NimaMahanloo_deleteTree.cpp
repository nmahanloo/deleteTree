// Nima Mahanloo
// DeleteTree
// CISP 430
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

struct tree
{
  int num = 0;
  tree* left = nullptr;
  tree* right = nullptr;
};

bool treeSearch (tree* root, int number)
{
    if (number == root->num)
    {
        return true;
    }
    else if ((root->left) && (number < root->num))
    {
        treeSearch(root->left, number);
    }
    else if ((root->right) && (number > root->num))
    {
        treeSearch(root->right, number);
    }
    else
        return false;
}

tree* findPlace (tree* curr, int number)
{
  if ((curr) && (curr->num > number))
  {
    if (curr->left)
    {
      findPlace (curr->left, number);
    }
    else
    {
      return curr;
    }
  }
  else if ((curr) && (curr->num < number))
  {
    if (curr->right)
    {
      findPlace (curr->right, number);
    }
    else
    {
      return curr;
    }
  }
}

void delNode (tree* (&leaf), int number)
{
  tree* temp = nullptr;
  if ((leaf) && (leaf->num == number))
  {
    if ((leaf->right) && (leaf->left))
    {
      temp = leaf->left;
      while (temp->right)
      {
        temp = temp->right;
      }
      temp->right = new tree;
      temp->right = leaf->right;
      temp = leaf;
      leaf = leaf->left;
      delete temp;
      temp = nullptr;
    }
    else if (leaf->left)
    {
      temp = leaf;
      leaf = leaf->left;
      delete temp;
      temp = nullptr;
    }
    else if (leaf->right)
    {
      temp = leaf;
      leaf = leaf->right;
      delete temp;
      temp = nullptr;
    }
    else
    {
      delete leaf;
      leaf = nullptr;
    }
  }
  else if ((leaf->left) && (leaf->left->num == number))
  {
    if ((leaf->left->right) && (leaf->left->left))
    {
      temp = leaf->left->left;
      while (temp->right)
      {
        temp = temp->right;
      }
      temp->right = new tree;
      temp->right = leaf->left->right;
      temp = leaf->left;
      leaf->left = leaf->left->left;
      delete temp;
      temp = nullptr;
    }
    else if (leaf->left->left)
    {
      temp = leaf->left;
      leaf->left = leaf->left->left;
      delete temp;
      temp = nullptr;
    }
    else if (leaf->left->right)
    {
      temp = leaf->left;
      leaf->left = leaf->left->right;
      delete temp;
      temp = nullptr;
    }
    else
    {
      delete leaf->left;
      leaf->left = nullptr;
    }
  }
  else if ((leaf->right) && (leaf->right->num == number))
  {
    if ((leaf->right->right) && (leaf->right->left))
    {
      temp = leaf->right->left;
      while (temp->right)
      {
        temp = temp->right;
      }
      temp->right = new tree;
      temp->right = leaf->right->right;
      temp = leaf->right;
      leaf->right = leaf->right->left;
      delete temp;
      temp = nullptr;
    }
    else if (leaf->right->left)
    {
      temp = leaf->right;
      leaf->right = leaf->right->left;
      delete temp;
      temp = nullptr;
    }
    else if (leaf->right->right)
    {
      temp = leaf->right;
      leaf->right = leaf->right->right;
      delete temp;
      temp = nullptr;
    }
    else
    {
      delete leaf->right;
      leaf->right = nullptr;
    }
  }
}

void delNum (tree* (&leaf), int number)
{
  if ((leaf) && (number > leaf->num))
  {
    if ((leaf->right) && (leaf->right->num == number))
    {
      delNode (leaf, number);
    }
    else if (leaf->right)
    {
      delNum (leaf->right, number);
    }
  }
  else if ((leaf) && (number < leaf->num))
  {
    if ((leaf->left) && (leaf->left->num == number))
    {
      delNode (leaf, number);
    }
    else if (leaf->left)
    {
      delNum (leaf->left, number);
    }
  }
  else if (leaf)
  {
    delNode (leaf, number);
  }
}

void pushNum (tree* root, tree* (&leaf), int number, bool firstNode)
{
  tree* curr = leaf;
  if (firstNode == false)
  {
    curr = findPlace (root, number);
    if (curr->num > number)
    {
      curr->left = new tree;
      curr = curr->left;
    }
    else if (curr->num < number)
    {
      curr->right = new tree;
      curr = curr->right;
    }
  }
  curr->num = number;
}

void readFile (tree* (&root))
{
  tree* leaf = root;
  bool firstNode = true;
  int number = 0;
  string inStr;
  ifstream readNum ("input.txt");
  if (readNum.is_open())
  {
    while (!(readNum.eof()))
    {
      bool numSearch = false;
      number = 0;
      readNum >> inStr;
      //cout << "str : " << inStr << endl;
      if (isdigit(inStr[0]) == false)
      {
        readNum >> number;
        //cout << "number : " << number << endl;
        numSearch = treeSearch(root, number);
        if (numSearch == true)
        {
          delNum (root, number);
        }
        else
        {
          pushNum (root, leaf, number, firstNode);
          firstNode = false;
        }
      }
      else
      {
        for (int i = 0; i < inStr.size(); i++)
        {
          number += (int(inStr[i])-48)*(pow(10, inStr.size()-1-i));
        }
        numSearch = treeSearch(root, number);
        if (numSearch == false)
        {
          pushNum (root, leaf, number, firstNode);
          firstNode = false;
        }
      }
    }
    readNum.close();
  }
  else
  {
    cout << "Error! Can't read input file!" << endl;
  }
}

void printTree (tree* leaf)
{
  cout << leaf->num << endl;
  if (leaf->left)
  {
    printTree (leaf->left);
  }
  if (leaf->right)
  {
    printTree (leaf->right);
  }
}

int main()
{
  tree* leaf = new tree;
  readFile (leaf);
  printTree (leaf);
  return 0;
}
