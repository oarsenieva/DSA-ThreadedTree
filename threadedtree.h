//Olga Arsenieva 067871137
//Assignment 3 DSA555


#include <iostream>
using namespace std;



//Threaded Tree class, creates a threaded tree, contains all necessary fields and functions
//and Node structure describing each Node, as well iterator and const_iterator classes
template <class T>
class ThreadedTree{
	
	//Node structure, creates one Node used in Tree, stores Node data, connections to children, and thread flags, and constructor
	struct Node{
		T data_;
		Node* left_;//node pointers
		Node* right_;
		bool leftIsThread_;//thread flags
		bool rightIsThread_;

		//Node constructor, receives data, pointers to child nodes, 
		//creates node with left and right threads if Nodes available
		Node(const T& data=T{},Node* left=nullptr, Node* right=nullptr){
		
			data_=data;
			left_=left;
			right_=right;
			leftIsThread_=true;
			rightIsThread_=true;
		}
	};

	Node* root_;	
	
	//print function, receives Node and level of tree, prints tree using inOrder traversal
	void print(const Node* rt)const{
		//I won't test this on the main.  You might find it useful
		//to implement for testing purposes
		//Note, passed in lvl so that you can use indentations based on lvl to 
		//see where a node is within your tree.  if you don't want to use it
		//just alter the prototype.
		
		if(rt!=nullptr){
			
			if(rt->left_ && !rt->leftIsThread_){
				print(rt->left_);
			}
			
			printNode(rt);
			
			if(rt->right_ && !rt->rightIsThread_ ){
				print(rt->right_);
			}
		}
	}

public:


	//const_iterator class creates an iterator that traverses the Threaded Tree,
	//contains const_iterator functions
	class const_iterator{
		
	protected:
	
		Node* curr_;
		
		//const_iterator constructor, creates iterator pointing at Node specified
		const_iterator(Node* c){curr_=c;}

	public:
	
	
		//iterator constructor for empty iterator
		const_iterator(){
			
			curr_=nullptr;
		}
	
	
		//operator++ postfix moves iterator to next/greater Node if available
		const_iterator operator++(int){
			
            const_iterator temp = *this;
			
			if(this->curr_ != nullptr){
				
				if( this->curr_->rightIsThread_) {//moving right by thread
			
					this->curr_ = this->curr_->right_;
				
				}else {//moving right by link
			
					this->curr_=this->curr_->right_;
					
					while(this->curr_->leftIsThread_ ==false){
						this->curr_=this->curr_->left_;
					}
				}
			}
		
			return temp;
		}
		
		
		//operator-- postfix moves const_iterator to previous/smaller Node if available
		const_iterator operator--(int){
			
            const_iterator temp = *this;
			
			if(this->curr_ != nullptr){
				
				if(this->curr_->leftIsThread_) {
					
					this->curr_ = this->curr_->left_;
				
				} else if(!this->curr_->leftIsThread_ ){
					
					this->curr_=this->curr_->left_;
					
					while(this->curr_->rightIsThread_ ==false){
						this->curr_=this->curr_->right_;
					}
				} 
			}
			
			return temp;
		}
		
		
		//dereferencing operator, returns data stored in Node const_iterator is pointing to
		const T& operator*(){
			
			if(this->curr_){
				
				return curr_->data_;
				
			} else{
				exit(1);
			}
		}
		
		
		//operator== receives reference to another const_iterator, 
		//returns true if it points to the same Node
		bool operator==(const const_iterator& rhs) const{
			return curr_ == rhs.curr_;
		}
		
		
		//operator!= receives reference to another const_iterator, 
		//returns true if it does not point to the same Node
		bool operator!=(const const_iterator& rhs) const{
			return curr_ != rhs.curr_;
		}
		
		
		friend class ThreadedTree;
	};

	
	//iterator class, creates an iterator that traverses the Threaded Tree,
	//contains iterator functions, inherits from const_iterator
	class iterator:public const_iterator{
		
		//iterator constructor-receives node, creates iterator pointing at it
		iterator(Node* c):const_iterator(c){}
		
	public:
	
	
		//iterator constructor for empty iterator
		iterator():const_iterator(){}
		
		
		//dereferencing operator, returns data stored in Node iterator is pointing to
		const T& operator*(){
			
			if(this->curr_){
				
				return this->curr_->data_;
				
			} else{
				exit(1);
			}
			
		}
		
		
		//operator++ postfix moves iterator to next/greater Node if available
		iterator operator++(int){
	        
			iterator temp = *this;
			
			if(this->curr_ != nullptr){
				
				if(this->curr_->rightIsThread_) {
					
					this->curr_ = this->curr_->right_;
				
				} else if(!this->curr_->rightIsThread_ ){
					
					this->curr_=this->curr_->right_;
					
					while(this->curr_->leftIsThread_ ==false){
						this->curr_=this->curr_->left_;
					}
				}
			}
			
			return temp;
		}
		
		
		//operator-- postfix moves iterator to previous/smaller Node if available
		iterator operator--(int){
			
			iterator temp = *this;
			
			if(this->curr_ != nullptr){
				
				if(this->curr_->leftIsThread_) {
					
					this->curr_ = this->curr_->left_;
				
				} else if(!this->curr_->leftIsThread_ ){
					
					this->curr_=this->curr_->left_;
					
					while(this->curr_->rightIsThread_ ==false){
						this->curr_=this->curr_->right_;
					}
				}
			}
			
			return temp;
		}
		
		
		friend class ThreadedTree;
	};

	
    //Tree constructor, creates empty threaded tree
	ThreadedTree(){
		
		root_=nullptr;
	}

	
	//receives pointer to Node, prints all information for one Node
	void printNode(const Node* node)const {
		
		if(node==nullptr){
			
			cout << "EMPTY NODE"<< endl;
			
		} else{
			
			cout << "Node=" << node;
			cout << "  left="<< node->left_<< " (red=" << node->leftIsThread_<<")";
			cout << "  right="<< node->right_ << " (red=" << node->rightIsThread_<<")";
			cout << " data=" << node->data_ << endl;
		}
	}
	
	
    //insert function, receives data, adds new Node to tree and inserts data
	//returns iterator pointing to new Node
	iterator insert(const T& data){
		
        iterator it;
        Node* node;
		
        if(root_){
			
            node=root_;
            bool done=false;
            Node* greater;
            Node* lesser;
			
            while(!done){
				
				if(data < node->data_ && node->leftIsThread_==false){
					
                    node=node->left_;
					
                } else if(data > node->data_ && node->rightIsThread_==false){
					
                    node=node->right_;
					
                } else if(data == node->data_) {
					
                    done=true;
					it.curr_=node;
					
                } else{
					
					if(data < node->data_){
						
						Node* nn=new Node(data, node->left_, node);
						node->left_=nn;
						node->leftIsThread_=false;
						done=true;
						it.curr_=nn;
						
					}else if(data > node->data_){
						
						Node* nn=new Node(data, node, node->right_);
						node->right_=nn;
						node->rightIsThread_=false;
						done=true;
						it.curr_=nn;
					}	
				}
            }
        } else {//if tree is empty
		
            root_=new Node(data);
            it=root_;
        }

        return it;
	}

	
	//search function, receives data, finds it in the Tree 
	//and returns iterator pointing at Node that holds it
	iterator find(const T& data) const{
		
        iterator it;
		Node* node;
	
        if(root_){
			
            node=root_; 
            bool done=false;
			
            while(done==false){
				
                if(data < node->data_ && node->leftIsThread_==false){
					
                    node=node->left_;
					
                } else if(data > node->data_ && node->rightIsThread_==false){
					
                    node=node->right_;
					
                } else if(data == node->data_) {
					
                    done=true;
					it.curr_=node;
					
                } else{
					
					done=true;
					it.curr_=nullptr;
				}
            }
        }
		
        return it;
	}

	
	//returns iterator pointing at smallest Node
	iterator begin(){

        iterator it;
		
        if(root_){
			
            it.curr_=root_;
			
            while(it.curr_->left_!=nullptr){
                it.curr_=it.curr_->left_;
			}
        }
		
        return it;
	}

	
	//returns iterator pointing to beyond last Node
	iterator end(){
		
        iterator it(nullptr);
        return it;
	}

	
	//returns const_iterator pointing at smallest Node
	const_iterator begin()const{
       		
        const_iterator it;
		
        if(root_){
			
            it.curr_=root_;
			
            while(it.curr_->left_!=nullptr){
                it.curr_=it.curr_->left_;
			}
        }
		
        return it;
	}

	
	//returns const_iterator pointing to beyond last Node
	const_iterator end() const{
		
        const_iterator it(nullptr);
        return it;
	}

	
	//prints Tree recursively starting from root
	void print() const{
		
		print(root_);
	}
	
	
	//Tree destructor, destroys Tree recursively
	~ThreadedTree(){
		//print();
		removeTree(root_);
		
	}
	
	
	//receives root of subtree, using postOrder traversal,
	//deletes each subtree of Node and then Node itself
	void removeTree(Node* sroot){
		
		if(sroot){
			
			if(!sroot->leftIsThread_){
				removeTree(sroot->left_);
			}
			
			if(!sroot->rightIsThread_){	
				removeTree(sroot->right_);
			}
			
			delete sroot;
			sroot=nullptr;
		}		
	}
};