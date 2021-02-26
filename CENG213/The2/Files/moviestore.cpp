#include "moviestore.h"


MovieStore::MovieStore( ) //implemented, do not change
{
}


// IMPLEMENT
void
MovieStore::insert(const Movie & movie)
{
  MSTP::Node *ptr;
  const MSTP::Node *ptr_const;
  primaryIndex.insert(movie.getID(), movie);
  ptr_const = primaryIndex.find(movie.getID());
  ptr = primaryIndex.find(movie.getID());
  secondaryIndex.insert(Movie::SecondaryKey(movie), &(ptr_const->data));
  ternaryIndex.insert(Movie::SecondaryKey(movie), &(ptr->data));
}


// IMPLEMENT
void
MovieStore::remove(const std::string & id)
{
  MSTP::Node *ptr;
  ptr = primaryIndex.find(id);
  if (ptr)
  {
    Movie::SecondaryKey SKeyToRemove(ptr->data);
    secondaryIndex.remove(SKeyToRemove);
    ternaryIndex.remove(SKeyToRemove);
    primaryIndex.remove(id);
  }
}


// IMPLEMENT
void
MovieStore::remove(const std::string & title,
                  const std::string & director)
{
  MSTS::Node *ptr;
  std::string idToDelete;
  Movie::SecondaryKey SKeyToRemove(title, director);
  ptr = secondaryIndex.find(SKeyToRemove);
  if (ptr)
  {
    idToDelete = ptr->data->getID();
    ternaryIndex.remove(SKeyToRemove);
    secondaryIndex.remove(SKeyToRemove);
    primaryIndex.remove(idToDelete);
  }
}


// IMPLEMENT
void
MovieStore::removeAllMoviesWithTitle(const std::string & title)
{
  std::string idToRemove;
  Movie::SecondaryKey KeyToRemove("", "");
  Movie::SecondaryKey LowerKey(title, "a");
  Movie::SecondaryKey UpperKey(title, "{");
  std::list<BinarySearchTree<SKey, Movie *, MovieBalanceCondition, TitleComparator>::Node *>::const_iterator itr;
  std::list<BinarySearchTree<SKey, Movie *, MovieBalanceCondition, TitleComparator>::Node *> ranges = ternaryIndex.find(LowerKey, UpperKey);
  for (itr = ranges.begin(); itr != ranges.end(); itr++)
  {
    idToRemove = (*itr)->data->getID();
    secondaryIndex.remove(Movie::SecondaryKey((*itr)->data->getTitle(), (*itr)->data->getDirector()));
    ternaryIndex.remove(Movie::SecondaryKey((*itr)->data->getTitle(), (*itr)->data->getDirector()));
    primaryIndex.remove(idToRemove);
  }
}


// IMPLEMENT
void
MovieStore::makeAvailable(const std::string & id)
{
  MSTP::Node *ptr;
  ptr = primaryIndex.find(id);
  if (ptr)
  {
    ptr->data.setAvailable();
  }
}


// IMPLEMENT
void
MovieStore::makeUnavailable(const std::string & title,
                           const std::string & director)
{
  MSTT::Node *ptr;
  Movie::SecondaryKey SKeyToRemove(title, director);
  ptr = ternaryIndex.find(SKeyToRemove);
  if (ptr)
  {
    ptr->data->setUnavailable();
  }
}


// IMPLEMENT
void
MovieStore::updateCompany(const std::string & director, 
                           const std::string & Company)
{
  const Movie *constPtrToUpdate;
  MSTP::Node *movToUpdate;
  Movie::SecondaryKey KeyToUpdate("", "");
  Movie::SecondaryKey LowerKey("a", director);
  Movie::SecondaryKey UpperKey("{", director);
  std::list<BinarySearchTree<SKey, const Movie *, MovieBalanceCondition, DirectorComparator>::Node *>::iterator itr;
  std::list<BinarySearchTree<SKey, const Movie *, MovieBalanceCondition, DirectorComparator>::Node *> ranges = secondaryIndex.find(LowerKey, UpperKey);
  for (itr = ranges.begin(); itr != ranges.end(); itr++)
  {
    constPtrToUpdate = (*itr)->data;
    movToUpdate = primaryIndex.find(constPtrToUpdate->getID());
    movToUpdate->data.setCompany(Company);
  }
}


// IMPLEMENT
void
MovieStore::printMoviesWithID(const std::string & id1,
                              const std::string & id2,
                              unsigned short since) const
{
  std::list<BinarySearchTree<std::string, Movie, MovieBalanceCondition>::Node *> ranges = primaryIndex.find(id1, id2);
  std::list<BinarySearchTree<std::string, Movie, MovieBalanceCondition>::Node *>::iterator itr;
  Movie *movToPrint;
  for(itr = ranges.begin(); itr != ranges.end(); itr++)
  {
    movToPrint = &((*itr)->data);
    if (movToPrint->getYear() >= since)
    {
      std::cout << *movToPrint << std::endl;
    }
  }
}


// IMPLEMENT
void
MovieStore::printMoviesOfDirector(const std::string & director,
                                  const std::string & first,
                                  const std::string & last) const
{
  Movie::SecondaryKey LowerKey(first, director);
  Movie::SecondaryKey UpperKey(last, director);
  const Movie *movToPrint;
  std::list<BinarySearchTree<SKey, const Movie *, MovieBalanceCondition, DirectorComparator>::Node *> ranges = secondaryIndex.find(LowerKey, UpperKey);
  std::list<BinarySearchTree<SKey, const Movie *, MovieBalanceCondition, DirectorComparator>::Node *>::iterator itr;
  for (itr = ranges.begin(); itr != ranges.end(); itr++)
  {
    movToPrint = (*itr)->data;
    std::cout << *movToPrint << std::endl;
  }
}



void  // implemented, do not change
MovieStore::printPrimarySorted( ) const
{
  printPrimarySorted(primaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printPrimarySorted(MSTP::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printPrimarySorted(t->left);
  std::cout << t->data << std::endl;
  printPrimarySorted(t->right);
}


void  // implemented, do not change
MovieStore::printSecondarySorted( ) const
{
  printSecondarySorted(secondaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printSecondarySorted(MSTS::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printSecondarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printSecondarySorted(t->right);
}


void  // implemented, do not change
MovieStore::printTernarySorted( ) const
{
  printTernarySorted(ternaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printTernarySorted(MSTT::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printTernarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printTernarySorted(t->right);
}

