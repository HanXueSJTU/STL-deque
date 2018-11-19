
#ifndef SJTU_DEQUE_HPP

#define SJTU_DEQUE_HPP



#include "exceptions.h"



#include <cstddef>
#include<cmath>
#include<iostream>



namespace sjtu {



template<class T>

class deque {

public:
    struct Node
    {
        T* val;
        Node* next;
        Node* pre;
        Node(T* v=NULL,Node* p=NULL,Node* n=NULL):val(v),next(n),pre(p){}
        ~Node(){delete val;};
    };

    struct Block
    {
        Node* first;
        Block* next;
        Block* pre;
        int block_len;
        Block(Node* f=NULL,Block* p=NULL,Block* n=NULL,int len=0)
        :first(f),pre(p),next(n),block_len(len){}
    };

	class const_iterator;

	class iterator {

	private:

		/**

		 * TODO add data members

		 *   just add whatever you want.

		 */

	public:
        Block *blo;
        Node *cur;
        deque *container;
        //int order;
        int posi;
		/**

		 * return a new iterator which pointer n-next elements

		 *   even if there are not enough elements, the behavior is **undefined**.

		 * as well as operator-

		 */

		 iterator(Block* b=NULL,Node* n=NULL,deque *c=NULL,int p=0)
		 :blo(b),cur(n),container(c),posi(p){}

		 iterator(const iterator&other)
		 :blo(other.blo),cur(other.cur),container(other.container),posi(other.posi){}



		iterator operator+(const int &n) const {
            iterator temp=*this;
            temp+=n;
            return temp;


			//TODO

		}

		iterator operator-(const int &n) const {
		    if (posi-n<0) throw invalid_iterator();
            iterator temp=*this;
            temp+=(-n);
            return temp;
			//TODO

		}

		// return th distance between two iterator,

		// if these two iterators points to different vectors, throw invaild_iterator.


		int operator-(const iterator &rhs) const {
		    if (container!=rhs.container) throw invalid_iterator();
		    return posi-rhs.posi;
			//TODO

		}

		iterator operator+=(const int &n) {
		    //std::cout<<"pos "<<posi<<" n "<<n<<" total "<<container->total<<"\n";
            int copyN=n,total=container->total;
            posi+=n;
            if ((posi>container->total or posi<0)and !(container->total==0 and posi==0))
                throw invalid_iterator();

            if (posi==container->total)
            {
                *this=container->finish;
                return *this;
            }
            if(posi==0)
            {
                *this=container->start;
                return *this;
            }

            if (n>0)
            {
                while(copyN>0 and cur->next!=NULL)
                {
                    cur=cur->next;
                    copyN--;
                }
                if (copyN>0)
                {
                    blo=blo->next;
                    while((copyN-(blo->block_len))>0)
                    {
                        copyN-=blo->block_len;
                        blo=blo->next;
                    }
                    cur=blo->first;
                    copyN--;
                    while(copyN>0)
                    {
                        cur=cur->next;
                        copyN--;
                    }
                }
            }
            else if (n<0)
            {
                while(copyN<0 and cur->pre!=NULL)
                {
                    cur=cur->pre;
                    copyN++;
                }
                if (copyN<0)
                {
                    blo=blo->pre;
                    while(copyN+blo->block_len<0)
                    {
                        copyN+=blo->block_len;
                        blo=blo->pre;
                    }
                    cur=blo->first;
                    copyN=blo->block_len+copyN;
                    while(copyN>0)
                    {
                        cur=cur->next;
                        copyN--;
                    }
                }

            }
            return *this;

			//TODO

		}

		iterator operator-=(const int &n) {
		    if (posi-n<0) throw invalid_iterator();
            *this+=(-n);
            return *this;
			//TODO

		}

		/**

		 * TODO iter++

		 */

		iterator operator++(int) {
            iterator temp=*this;
            ++*this;
            return temp;
		}

		/**

		 * TODO ++iter

		 */

		iterator& operator++() {
            if (cur->next)
                cur=cur->next;
            else if (blo->next)
            {
                blo=blo->next;
                cur=blo->first;
            }
            else
                throw invalid_iterator();
            posi++;
            return *this;
		}

		/**

		 * TODO iter--

		 */

		iterator operator--(int) {
            iterator temp=*this;
            --*this;
            return temp;
		}

		/**

		 * TODO --iter

		 */

		iterator& operator--() {
            if(cur->pre)
                cur=cur->pre;
            else if (blo->pre)
            {
                blo=blo->pre;
                cur=blo->first;
                while(cur->next)
                    cur=cur->next;
            }
            else throw invalid_iterator();
            posi--;
            return *this;
		}

		/**

		 * TODO *it

		 */

		T& operator*() const
		{
		    if (posi==container->total)
            {
		    throw invalid_iterator();
		    }
		    return *(cur->val);
        }

		/**

		 * TODO it->field

		 */

		T* operator->() const noexcept {return cur->val;}

		/**

		 * a operator to check whether two iterators are same (pointing to the same memory).

		 */

		bool operator==(const iterator &rhs) const {return cur==rhs.cur;}

		bool operator==(const const_iterator &rhs) const {return cur==rhs.cur;}

		/**

		 * some other operator for iterator.

		 */

		bool operator!=(const iterator &rhs) const {return cur!=rhs.cur;}

		bool operator!=(const const_iterator &rhs) const {return cur!=rhs.cur;}

	};

	class const_iterator {

		// it should has similar member method as iterator.

		//  and it should be able to construct from an iterator.

    private:

			// data members.

    public:

        Block *blo;
        Node *cur;
        deque *container;
        int posi;

       const_iterator(Block* b=NULL,Node* n=NULL,deque *c=NULL,int p=0)
		 :blo(b),cur(n),container(c),posi(p){}

        const_iterator(const const_iterator &other)
        : blo(other.blo),cur(other.cur),container(other.container),posi(other.posi)
        {

				// TODO

        }

        const_iterator(const iterator &other)
        : blo(other.blo),cur(other.cur),container(other.container),posi(other.posi)
        {

				// TODO

        }

			// And other methods in iterator.

			// And other methods in iterator.

			// And other methods in iterator.



		const_iterator operator+(const int &n) const {
            const_iterator temp=*this;
            temp+=n;
            return temp;



			//TODO

		}

		const_iterator operator-(const int &n) const {
		    if (posi-n<0) throw invalid_iterator();
            const_iterator temp=*this;
            temp+=(-n);
            return temp;
			//TODO

		}

		// return th distance between two iterator,

		// if these two iterators points to different vectors, throw invaild_iterator.


		int operator-(const const_iterator &rhs) const {
		    if (container!=rhs.container) throw invalid_iterator();
		    return posi-rhs.posi;

			//TODO

		}

		const_iterator operator+=(const int &n) {
            int copyN=n;
            posi+=n;
            if ((posi>container->total or posi<0)and !(container->total==0 and posi==0))
                throw invalid_iterator();
            if (posi==container->total)
            {
                *this=container->finish;
                return *this;
            }
            if(posi==0)
            {
                *this=container->start;
                return *this;
            }
            if (n>0)
            {
                while(copyN>0 and cur->next!=NULL)
                {
                    cur=cur->next;
                    copyN--;
                }
                if (copyN>0)
                {
                    blo=blo->next;
                    while((copyN-(blo->block_len))>0)
                    {
                        copyN-=blo->block_len;
                        blo=blo->next;
                    }
                    cur=blo->first;
                    copyN--;
                    while(copyN>0)
                    {
                        cur=cur->next;
                        copyN--;
                    }
                }
            }
            else if (n<0)
            {
                while(copyN<0 and cur->pre!=NULL)
                {
                    cur=cur->pre;
                    copyN++;
                }
                if (copyN<0)
                {
                    blo=blo->pre;
                    while(copyN+blo->block_len<0)
                    {
                        copyN+=blo->block_len;
                        blo=blo->pre;
                    }
                    cur=blo->first;
                    copyN=blo->block_len+copyN;
                    while(copyN>0)
                    {
                        cur=cur->next;
                        copyN--;
                    }
                }

            }
            else
                return *this;


			//TODO

		}

		const_iterator operator-=(const int &n) {
		    if (posi-n<0) throw invalid_iterator();
            *this+=(-n);
            return *this;
			//TODO

		}

		/**

		 * TODO iter++

		 */

		const_iterator operator++(int) {
            const_iterator temp=*this;
            ++*this;
            return temp;
		}

		/**

		 * TODO ++iter

		 */

		const_iterator& operator++() {
            if (cur->next)
                cur=cur->next;
            else if (blo->next)
            {
                blo=blo->next;
                cur=blo->first;
            }
            else throw invalid_iterator();
            posi++;
            return *this;
		}

		/**

		 * TODO iter--

		 */

		const_iterator operator--(int) {
            const_iterator temp=*this;
            --*this;
            return temp;
		}

		/**

		 * TODO --iter

		 */

		const_iterator& operator--() {
            if(cur->pre)
                cur=cur->pre;
            else if (blo->pre)
            {
                blo=blo->pre;
                cur=blo->first;
                while(cur->next)
                    cur=cur->next;
            }
            else throw invalid_iterator();
            posi--;
            return *this;
		}

		/**

		 * TODO *it

		 */

		T& operator*() const
		{
		    if (posi==container->total)
                throw invalid_iterator();
		    return *(cur->val);
        }

		/**

		 * TODO it->field

		 */

		T* operator->() const noexcept {return cur->val;}

		/**

		 * a operator to check whether two iterators are same (pointing to the same memory).

		 */

		bool operator==(const iterator &rhs) const {return cur==rhs.cur;}

		bool operator==(const const_iterator &rhs) const {return cur==rhs.cur;}

		/**

		 * some other operator for iterator.

		 */

		bool operator!=(const iterator &rhs) const {return cur!=rhs.cur;}

		bool operator!=(const const_iterator &rhs) const {return cur!=rhs.cur;}


	};


    int total;
    iterator start;
    iterator finish;
    iterator current;

	/**

	 * TODO Constructors

	 */
    int stdLen() {return 100>sqrt(total)?100:sqrt(total);}

	deque()
	{
	    total=0;
	    Node* endOne=new Node();
	    finish.container=this;
	    finish.cur=endOne;
	    finish.posi=total;
	    start=finish;
	    current=finish;
    }

	deque(const deque &other):total(other.total)
	{
	    if (other.empty())
        {
            total=0;
            Node* endOne=new Node();
            finish.container=this;
            finish.cur=endOne;
            finish.posi=total;
            start=finish;
        }
        else
        {
            Block *curBlock,*otherBlock=other.start.blo,*preBlock=NULL;
            Node *temp,*tempNew,*preNode;
            T* value;
            while (otherBlock!=NULL)
            {
                temp=otherBlock->first;
                value=new T(*(temp->val));
                tempNew=new Node(value,NULL,NULL);
                curBlock=new Block(tempNew,preBlock,NULL,otherBlock->block_len);
                if (preBlock!=NULL)
                {
                    preBlock->next=curBlock;
                }
                else
                {
                    start.blo=curBlock;
                    start.container=this;
                    start.cur=tempNew;
                    start.posi=0;
                }

                preNode=tempNew;
                while(temp->next and temp->next->val!=NULL)
                {
                    temp=temp->next;
                    value=new T(*(temp->val));
                    tempNew=new Node(value,preNode,NULL);
                    preNode->next=tempNew;
                    preNode=tempNew;
                }

                otherBlock=otherBlock->next;
                preBlock=curBlock;
            }



            finish.blo=preBlock;
            preBlock->next=NULL;
            finish.container=this;
            finish.posi=total;
            temp=new Node(NULL,preNode,NULL);
            preNode->next=temp;
            finish.cur=temp;
            current=start;


        }

	}


	/**

	 * TODO Deconstructor

	 */

	~deque()
	{
        clear();
        if (finish.cur)
            delete finish.cur;
        finish.cur=NULL;
	}

	/**

	 * TODO assignment operator

	 */

	deque &operator=(const deque &other)
	{
        if (&other==this)
            return *this;
        clear();
        if (other.empty())
        {
            total=0;
            finish.blo=NULL;
            finish.posi=0;
            start=finish;
            return *this;
        }
	    total=other.total;
        Block *curBlock,*otherBlock=other.start.blo,*preBlock=NULL;
	    Node *temp,*tempNew,*preNode;
	    T* value;
	    while (otherBlock)
        {
            temp=otherBlock->first;
            value=new T(*(temp->val));
            tempNew=new Node(value);
            curBlock=new Block(tempNew,preBlock,NULL,otherBlock->block_len);
            if (preBlock!=NULL)
                preBlock->next=curBlock;
            else
            {
                start.blo=curBlock;
                start.container=this;
                start.cur=tempNew;
                start.posi=0;
            }

            preNode=tempNew;
            while(temp->next and temp->next->val!=NULL)
            {
                temp=temp->next;
                value=new T(*(temp->val));
                tempNew=new Node(value,preNode,NULL);
                preNode->next=tempNew;
                preNode=tempNew;
            }

            otherBlock=otherBlock->next;
            preBlock=curBlock;
        }

        finish.blo=preBlock;
        finish.posi=total;
        preNode->next=finish.cur;
        finish.cur->pre=preNode;
        current=start;
        return *this;
	}

	/**

	 * access specified element with bounds checking

	 * throw index_out_of_bound if out of bound.

	 */

	T & at(const int &pos)
	{
	    if (pos>total-1 or pos<0)
            throw index_out_of_bound();
        int dis=current.posi-pos;
        current-=dis;
        return *current;
    }

	const T & at(const int &pos) const
	{
	    if (pos>total-1 or pos<0)
            throw index_out_of_bound();
        //int dis=pos-current.posi;
        //current+=dis;
        return *(start+pos);
    }

	T & operator[](const int &pos)
	{
	    if (pos>total-1 or pos<0)
        {
            throw index_out_of_bound();
        }
        int dis=pos-current.posi;
        current+=dis;
        return *current;
    }

	const T & operator[](const int &pos) const
	{
	    if (pos>total-1 or pos<0)
        {
            throw index_out_of_bound();
        }
        //int dis=pos-current.posi;
        //current+=dis;
        return *(start+pos);
    }

	/**

	 * access the first element

	 * throw container_is_empty when the container is empty.

	 */

	const T & front() const
	{
        if (total==0)
            throw container_is_empty();
        return *start;
	}

	/**

	 * access the last element

	 * throw container_is_empty when the container is empty.

	 */

	const T & back() const
	{
        if (total==0)
            throw container_is_empty();
        return *(finish.cur->pre->val);
	}

	/**

	 * returns an iterator to the beginning.

	 */

	iterator begin() {return start;}

	const_iterator cbegin() const {return const_iterator(start);}

	/**

	 * returns an iterator to the end.

	 */

	iterator end() {return finish;}

	const_iterator cend() const {return const_iterator(finish);}

	/**

	 * checks whether the container is empty.

	 */

	bool empty() const {return total==0;}

	/**

	 * returns the number of elements

	 */

	int size() const {return total;}

	/**

	 * clears the contents

	 */

	void clear()
	{
	    if (total==0)
            return;
	    total=0;
        Block *tempBlock=start.blo,*oldBlock;
        Node *tempNode,*oldNode;
        while (tempBlock)
        {
            tempNode=tempBlock->first;
            oldNode=tempNode;
            while(oldNode!=NULL and oldNode->val!=NULL)
            {
                tempNode=tempNode->next;
                delete oldNode;
                oldNode=tempNode;
            }
            oldBlock=tempBlock;
            tempBlock=tempBlock->next;
            delete oldBlock;
        }

        start=finish;
        finish.posi=total;
        current=start;
	}

	/**

	 * inserts elements at the specified locat on in the container.

	 * inserts value before posi

	 * returns an iterator pointing to the inserted value

	 *     throw if the iterator is invalid or it point to a wrong place.

	 */

	iterator insert(iterator pos, const T value)
	{

        if (pos==start)
        {
            push_front(value);
            return start;
        }
        if(pos==finish)
        {
            push_back(value);
            return (finish-1);
        }
	    if (pos.posi<0 or pos.posi>total-1 or pos.container!=this)
            throw invalid_iterator();


        total++;
        finish.posi=total;
        T* val=new T(value);
        Node *oldNode=pos.cur;
        Node *newNode=new Node(val,oldNode->pre,oldNode);

        if (oldNode->pre==NULL)
            pos.blo->first=newNode;
        else
            oldNode->pre->next=newNode;
        oldNode->pre=newNode;
        pos.blo->block_len++;
        pos.cur=newNode;



        resize(pos.blo,pos);
        current=start;

        return pos;
	}

	/**

	 * removes specified element at posi.

	 * removes the element at posi.

	 * returns an iterator pointing to the following element, if posi pointing to the last element, end() will be returned.

	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.

	 */

	iterator erase(iterator pos)
	{

        if (pos.posi<0 or pos.posi>total-1 or pos.container!=this or total==0)
            throw invalid_iterator();

        if (pos==start)
        {
            pop_front();
            return start;
        }
        if(pos.posi==total-1)
        {
            pop_back();
            return finish;
        }

        total--;

        if (total==0)
        {
            destory();
            return finish;
        }


        Block* oldBlock=pos.blo;
        Node* oldNode=pos.cur;
        finish.posi=total;
        oldBlock->block_len--;


        if (oldNode->pre==NULL)
        {
            pos.cur=pos.cur->next;
            pos.cur->pre=NULL;
            oldBlock->first=pos.cur;
        }
        else if(oldNode->next==NULL)
        {
            oldNode->pre->next=NULL;
            pos.blo=pos.blo->next;
            pos.cur=pos.blo->first;
        }
        else
        {
            pos.cur=pos.cur->next;
            oldNode->pre->next=pos.cur;
            pos.cur->pre=oldNode->pre;
        }
        delete oldNode;
        resize(oldBlock,pos);
        current=start;
        return pos;
	}

	/**

	 * adds an element to the end

	 */

	void push_back(const T &value)
	{
	    if (total==0)
        {
            create(value);
            return;
        }
	    total++;
        T* val=new T(value);
        Node *temp=new Node(val,finish.cur->pre,finish.cur);
        finish.cur->pre=temp;
        temp->pre->next=temp;
        finish.blo->block_len++;
        finish.posi=total;
        resize(finish.blo,start);
	}

	/**

	 * removes the last element

	 *     throw when the container is empty.

	 */

	void pop_back()
	{
	    if (total==0)
            throw container_is_empty();
        total--;
        if (total==0)
        {
            destory();
            return;
        }

        Node* temp=finish.cur->pre;
        if (temp->pre==NULL)
        {
            Block *tempBlock=finish.blo;
            finish.blo=finish.blo->pre;
            finish.blo->next=NULL;
            temp=finish.blo->first;
            while(temp->next)
                temp=temp->next;
            finish.cur->pre=temp;
            temp->next=finish.cur;

            delete tempBlock->first;
            delete tempBlock;
        }
        else
        {
            finish.cur->pre=temp->pre;
            temp->pre->next=finish.cur;
            finish.blo->block_len--;
            delete temp;
        }
        finish.posi=total;
        resize(finish.blo,start);
	}

	/**

	 * inserts an element to the beginning.

	 */

	void push_front(const T &value)
	{
	    if (total==0)
        {
            create(value);
            return;
        }
        total++;
        T* val=new T(value);
        Node* temp=new Node(val,NULL,start.cur);

        start.cur->pre=temp;
        start.cur=temp;
        start.blo->first=temp;
        start.blo->block_len++;
        finish.posi=total;
        resize(start.blo,start);
        current=start;
	}



	/**

	 * removes the first element.

	 *     throw when the container is empty.

	 */

	void pop_front()
	{
        if(total==0)
            throw container_is_empty();
        total--;
        if (total==0)
        {
            destory();
            return;
        }


        Node* temp=start.cur->next;
        if (temp==NULL)
        {
            Block* tempBlock=start.blo;
            start.blo=start.blo->next;
            start.cur=start.blo->first;
            start.blo->pre=NULL;
            delete tempBlock->first;
            delete tempBlock;
        }
        else
        {
            start.cur=temp;
            start.blo->block_len--;
            start.blo->first=temp;
            temp=temp->pre;
            start.cur->pre=NULL;
            delete temp;
        }
        finish.posi==total;
        resize(start.blo,start);
        current=start;
	}


	void create(const T &value)
	{
	    total=1;
        T* val=new T(value);
	    Node* newNode=new Node(val,NULL,finish.cur);
        Block* NewBlock=new Block(newNode,NULL,NULL,1);
        start.blo=NewBlock;
        start.container=this;
        start.cur=newNode;
        start.posi=0;
        current=start;

        finish.blo=NewBlock;
        finish.cur->pre=newNode;
        finish.posi=total;
	}

	void destory()
	{
	    total=0;
	    finish.cur->pre=NULL;
	    finish.blo=NULL;
	    finish.posi=0;
	    delete start.cur;
	    delete start.blo;
	    start=finish;
	    current=start;
	}



	void resize(Block* blo1,iterator& iterIn)
	{
        if(blo1->block_len>=2*stdLen())
        {
            bool isIn=false;
            int order=1,newSize=blo1->block_len/2;
            Node* temp=blo1->first->next;
            while(order<newSize)
            {
                if (temp==iterIn.cur)
                    isIn=true;
                order++;
                temp=temp->next;
            }
            Block* newBlock=new Block(temp,blo1,blo1->next,blo1->block_len-order);
            if (blo1->next)
                blo1->next->pre=newBlock;
            blo1->next=newBlock;
            blo1->block_len=order;

            temp->pre->next=NULL;
            temp->pre=NULL;
            if (isIn==false and iterIn!=start)
                iterIn.blo=newBlock;
            if (finish.blo==blo1)
                finish.blo=newBlock;

        }
        if(blo1->block_len<stdLen()/2)
        {
            if (blo1->next!=NULL and (blo1->next->block_len+blo1->block_len)<stdLen()*2)
            {
                Block* tempBlock=blo1->next;
                Node* tempNode=blo1->first;

                if(iterIn!=start and iterIn.blo==blo1->next)
                    iterIn.blo=blo1;
                if (finish.blo==blo1->next)
                    finish.blo=blo1;

                while(tempNode->next!=NULL)
                    tempNode=tempNode->next;

                tempNode->next=tempBlock->first;
                tempBlock->first->pre=tempNode;

                blo1->next=tempBlock->next;
                if (tempBlock->next)
                    tempBlock->next->pre=blo1;
                blo1->block_len+=tempBlock->block_len;
                delete tempBlock;
            }
            else if (blo1->pre!=NULL and (blo1->pre->block_len+blo1->block_len)<stdLen()*2)
            {
                Block* tempBlock=blo1->pre;
                Node* tempNode=tempBlock->first;

                if(iterIn!=start and iterIn.blo==blo1)
                    iterIn.blo=tempBlock;
                if (finish.blo==blo1)
                    finish.blo=tempBlock;

                while(tempNode->next!=NULL)
                    tempNode=tempNode->next;

                tempNode->next=blo1->first;
                blo1->first->pre=tempNode;
                tempBlock->next=blo1->next;
                if (blo1->next)
                    blo1->next->pre=tempBlock;
                tempBlock->block_len+=blo1->block_len;
                delete blo1;
            }

        }
	}

};



}



#endif
