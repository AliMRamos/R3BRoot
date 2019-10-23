#include <TIterator.h> // 
namespace roothacks
{
  template <class T>
  struct TCAHelper
  {
    template <class ... Args>
    static T* AddNew(TClonesArray& tca, Args... args)
    {
      return new(tca[tca.GetEntriesFast()]) T(args...);
    }
  };

  // a std-compatible wrapper for the so-called Iterator of ROOT.
  template<class T>
  class wrappedIterator: public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    wrappedIterator(TIter c): 
      pseudoIt(c)
    { 
    }
    
    T& operator*()
    {
      return dynamic_cast<T&>(**(this->pseudoIt));
    }
      
    wrappedIterator& operator++()
    {
      this->pseudoIt.Next();
      return *this;
    }
  
    bool operator!=(wrappedIterator& rhs)
    {
      return this->pseudoIt!=rhs.pseudoIt;
    }

    bool operator==(wrappedIterator& rhs)
    {
      //*someone* did not bother to overload operator==
      return !(this->pseudoIt!=rhs.pseudoIt);
    }
  protected:
    TIter pseudoIt;
  };

  template<class T, class ColType>
  class wrappedCollection
  {
  public:
    wrappedCollection(ColType* pseudoCollection):
      pseudoCol(pseudoCollection)
    {
    }
    
    wrappedIterator<T> begin() const
    {
      return wrappedIterator<T>(TIter(pseudoCol).Begin());
    }
    wrappedIterator<T> end() const
    {
      return wrappedIterator<T>(TIter(pseudoCol).End());
    }
  protected:
    ColType* pseudoCol;
  };

  template <class T>
  struct TypedCollection
  {
    template <class ColType>
    static wrappedCollection<T, ColType> cast(ColType* col)
    {
      return wrappedCollection<T, ColType>(col);
    }
  };
  

}; //namespace roothacks
