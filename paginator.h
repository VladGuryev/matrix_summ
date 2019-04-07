#ifndef PAGINATOR_H
#define PAGINATOR_H

#include <iostream>
#include <vector>
#include <iterator>

using namespace  std;

template<typename Iterator>
class Page {
  Iterator bound1;
  Iterator bound2;
public:
  typedef Iterator iterator;
  typedef Iterator const_iterator;

  Page(Iterator begin, Iterator end): bound1(begin), bound2(end){}

  size_t size() const {
    return bound2 - bound1;
  }

  const_iterator begin() const{return bound1;}
  const_iterator end() const {return bound2;}

  iterator begin() {return bound1;}
  iterator end()  {return bound2;}
};

template<typename Iterator>
Page<Iterator> makePage(Iterator begin, Iterator end){
  return {begin, end};
}

template <typename Iterator>
class Paginator {
  Iterator first;
  Iterator last;
  size_t m_page_size;
  vector<Page<Iterator>> pages;
public:
  Paginator(Iterator begin, Iterator end, size_t page_size)
  {
    Iterator left_it = begin;
    Iterator right_it = next(begin, page_size);
    size_t range_size = distance(begin, end);

    for(size_t page_number = 0; page_number < (range_size / page_size);
        page_number++)
    {
      pages.push_back(makePage(left_it, right_it));
      left_it = next(left_it, page_size);
      right_it = next(right_it, page_size);
    }
    if(prev(right_it, page_size) != end){
      pages.push_back(makePage(left_it, end));
    }
  }

  typename vector<Page<Iterator>>::const_iterator begin() const{return pages.begin();}
  typename vector<Page<Iterator>>::const_iterator  end() const{return pages.end();}
  typename vector<Page<Iterator>>::iterator begin() {return pages.begin();}
  typename vector<Page<Iterator>>::iterator  end() {return pages.end();}

  size_t size() const {
    return pages.size();
  }
};

template <typename Container>
Paginator<typename Container::iterator>
Paginate(Container& c, size_t page_size) {
  return {c.begin(), c.end(), page_size};
}

template <typename Container>
Paginator<typename Container::const_iterator> //да, я знаю что можно auto, но это в С++17, а я на С++14
Paginate(const Container& c, size_t page_size) {
  return {c.begin(), c.end(), page_size};
}


#endif // PAGINATOR_H
