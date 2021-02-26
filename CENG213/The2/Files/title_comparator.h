#ifndef _title_h__
#define _title_h__

#include "movie.h"
#include <cstring>


class TitleComparator
{
  public:
    // IMPLEMENT BELOW (inline)
    bool operator( ) (const Movie::SecondaryKey & key1, 
                      const Movie::SecondaryKey & key2) const
    {
      std::string title1, title2, director1, director2;
      std::string title1Lower, title2Lower, director1Lower, director2Lower;
      std::string::const_iterator itr_const;
      char currChar;
      int titleComp, directorComp;
      title1.assign(key1.getTitle());
      for (itr_const = title1.begin(); itr_const != title1.end(); itr_const++)
      {
        currChar = *itr_const;
        if (currChar <= 'z' && currChar >= 'a')
        {
          title1Lower.push_back(currChar);
        }
        else if (currChar <= 'Z' && currChar >= 'A')
        {
          title1Lower.push_back(currChar+'a'-'A');
        }
        else
        {
          title1Lower.push_back(currChar);
        }
      }

      title2.assign(key2.getTitle());
      for (itr_const = title2.begin(); itr_const != title2.end(); itr_const++)
      {
        currChar = *itr_const;
        if (currChar <= 'z' && currChar >= 'a')
        {
          title2Lower.push_back(currChar);
        }
        else if (currChar <= 'Z' && currChar >= 'A')
        {
          title2Lower.push_back(currChar+'a'-'A');
        }
        else
        {
          title2Lower.push_back(currChar);
        }
      }
      titleComp = title1Lower.compare(title2Lower);
      if (titleComp < 0)
      {
        return true;
      }
      else if (titleComp > 0)
      {
        return false;
      }
      else
      {
        director1.assign(key1.getDirector());
        for (itr_const = director1.begin(); itr_const != director1.end(); itr_const++)
        {
          currChar = *itr_const;
          if (currChar <= 'z' && currChar >= 'a')
          {
            director1Lower.push_back(currChar);
          }
          else if (currChar <= 'Z' && currChar >= 'A')
          {
            director1Lower.push_back(currChar+'a'-'A');
          }
          else
          {
            director1Lower.push_back(currChar);
          }
        }

        director2.assign(key2.getDirector());
        for (itr_const = director2.begin(); itr_const != director2.end(); itr_const++)
        {
          currChar = *itr_const;
          if (currChar <= 'z' && currChar >= 'a')
          {
            director2Lower.push_back(currChar);
          }
          else if (currChar <= 'Z' && currChar >= 'A')
          {
            director2Lower.push_back(currChar+'a'-'A');
          }
          else
          {
            director2Lower.push_back(currChar);
          }
        }
        directorComp = director1Lower.compare(director2Lower);
        if (directorComp < 0)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    }
};

#endif
