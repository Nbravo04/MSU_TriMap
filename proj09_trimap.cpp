/*
Nicholas Bravata
Project 09 Trimap
Section 003
11/20/2017
*/
#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;
#include<iterator>
using std::ostream_iterator; using std::back_inserter;
#include<algorithm>
using std::copy; using std::upper_bound; using std::find;using std::lower_bound;
using std::binary_search;
#include<initializer_list>
using std::initializer_list;
#include<new>


#include "proj09_trimap.h"
//TriMap Constructor for a single element e
TriMap::TriMap(const Element& e)
{
  vec_.push_back(e);
  sz_=vec_.size();
}

//TriMap Constructor fo a list of Elements
TriMap::TriMap(initializer_list<Element>list)
{
  vec_ = list;
  sz_= vec_.size();
}

//Makes a operator<< able to output Element Class
ostream& operator<<(ostream& out, const Element& elem)
{
  ostringstream oss;

  oss<<elem.key_<<":"<< elem.value_<<":"<< elem.index_;

  string s = oss.str();
  out << s;

  return out;
}

//Returns the size of the TriMap.
size_t TriMap::size()
{
  return vec_.size();
}

//Inserts new element with just a key and value into the TriMap. Assigns it a index number for when it was added.
bool TriMap::insert(string key,string value)
{
  bool ret_val=false;
  long index = vec_.size();
  Element e(key,value,index);
  int n=0;//If n!=0 then key is already in TriMap

  for(auto iter=vec_.begin(); iter != vec_.end();iter++)
  {
    string e_key = iter->key_;
    if(e_key == key)
      n++;
  }

  if(n!=0)
    return ret_val;
  else
  {
    int idx=0;
    ret_val = true;
    for(auto iter_2=vec_.begin(); iter_2 != vec_.end();iter_2++)
    {
      string e_key = iter_2->key_;
      if(key < e_key)
      {
        vec_.insert(vec_.begin()+idx, e);
        break;
      }
      else
        idx++;
    }
    int i=0;
    for(auto iter3=vec_.begin(); iter3 != vec_.end();iter3++)
    {
      string e_key = iter3->key_;
      if(e_key == key)
        i++;
    }
    if (i==0)
      vec_.push_back(e);
    return ret_val;
  }

}

//Checks to see if the key exists in the TriMap. If it is the function removes it from the map and then updats each elements index above the index of the take number.
bool TriMap::remove(string key_str)
{
  auto removed_ele = find_key(key_str);
  if (removed_ele)
    {
      size_t removed_index = removed_ele->index_;
      int index=0;
      for (auto iter=vec_.begin(); iter != vec_.end();iter++)
      {
          string v_key = iter->key_;
          if (key_str==v_key)
          {
              vec_.erase(vec_.begin()+index);
              for (auto iter_=vec_.begin(); iter_ != vec_.end();iter_++)
              {
                  size_t v_index = iter_->index_;
                  //if (v_index > removed_index)
                    //iter_->key_--;
              }
          }
          else
            index++;
      }
      return true;
    }
  else
    return false;
}

//Uses binary_search and other methods to locate a key in a TriMap. Returns a ptr element that points to that element
Element* TriMap::find_key(const string& key_str)
{
  Element e2(key_str, "value", 0);
  vector<Element>::iterator pos;
  pos = upper_bound(vec_.begin(), vec_.end(), e2,[=](const Element &e, const Element &e2)
  {
  return e2.key_==e.key_;
 });
 if (pos == vec_.end() )
    return nullptr;
  else
    return &(*pos);
}

//This function locates a elements within the TriMap that has the value inputed. Returns a element pointer that points to the element with the matching value.
Element* TriMap::find_value(const string& value)
{
  Element* ptr_elem;
  int n=0;
  for (auto iter=vec_.begin(); iter!=vec_.end();iter++)
  {
    string trimap_val = iter->value_;
    if(value == trimap_val)
    {
      ptr_elem = &iter[0];
      n++;
      break;
    }
  }
  if (n!=0)
    return ptr_elem;
  else
    return nullptr;
}

//This function locates a elements within the TriMap that has the index inputed. Returns a element pointer that points to the element with the matching index.
Element* TriMap::find_index(size_t index)
{
  Element* ptr_elem;
  int n=0;
  for (auto iter=vec_.begin(); iter!=vec_.end();iter++)
  {
    size_t trimap_idx = iter->index_;
    if(index == trimap_idx)
    {
      ptr_elem = &iter[0];
      n++;
      break;
    }
  }
  if (n!=0)
    return ptr_elem;
  else
    return nullptr;
}

//Makes a operator<< able to output TriMap Class
ostream& operator<<(ostream& out, const TriMap& map)
{
  ostringstream oss;

  for (auto iter=map.vec_.begin(); iter!=map.vec_.end();iter++)
    {
      if(iter+1!=map.vec_.end())
        oss<< iter[0]<<", ";
      else
        oss<< iter[0];
    }

  string s = oss.str();
  out << s;

  return out;
}
