#ifndef BST_H
#define BST_H

template<typename T>
class BSTNode{

	T key;
	BSTNode<T>* parent;
	BSTNode<T>* right;
	BSTNode<T>* left;
	bool verbose;

	template<typename C>
	friend class BST;

public:

	BSTNode(T key, bool verbose = false) : key(key), verbose(verbose){
		parent = nullptr;
		right = nullptr;
		left = nullptr;
	}

	//Getter
	BSTNode<T>* getParent(){return this->parent;}
	BSTNode<T>* getRight(){return this->right;}
	BSTNode<T>* getLeft(){return this->left;}
	T getKey(){return this->key;}

	//Setter
	void setParent(BSTNode<T>* parent){this->parent = parent;}
	void setRight(BSTNode<T>* right){this->right = right;}
	void setLeft(BSTNode<T>* left){this->left = left;}
	void setKey(T key){this->key = key;}

	friend ostream& operator<< (ostream& os, const BSTNode<T>& b){

		if(b.verbose){
			os << "BSTNode: " << &b << endl;
			os << "Key =" << b.key << endl;
			os << "left->" << b.left << "\t right->" << b.right << "\t parent->" << b.parent << endl;
			return os;
		}

		return os << "Key = " << b.key << endl;
	}
	
};

template<typename T>
class BST{
	
		BSTNode<T>* root;

	public:

		BST(){root = nullptr;}
		
		BSTNode<T>* getRoot(){return this->root;}

		bool isEmpty(){return root == nullptr;}

		void insert(T key){
			
			if(isEmpty())
			{
				root = new BSTNode<T>(key);
				return;
			}

			insert(root, key);
		}

		void insert(BSTNode<T>* ptr, T key){

			if(!ptr->left && key <= ptr->key)
			{
				ptr->left = new BSTNode<T>(key);
				ptr->left->setParent(ptr);
				return;
			}

			if(!ptr->right && key > ptr->key)
			{
				ptr->right = new BSTNode<T>(key);
				ptr->right->setParent(ptr);
				return;
			}

			if(key <= ptr->key)
				insert(ptr->left, key);

			else
				insert(ptr->right, key);
		}

		void visit(BSTNode<T>* ptr) { cout << "\n" << *ptr << endl; }

		void pre_order(BSTNode<T>* ptr){

			if(!ptr)
				return;

			visit(ptr);
			pre_order(ptr->left);
			pre_order(ptr->right);
		}

		void pre_order(){pre_order(root);}
 
		void in_order(BSTNode<T>* ptr){

			if(!ptr)
				return;

			in_order(ptr->left);
			visit(ptr);
			in_order(ptr->right);
		}

		void in_order(){in_order(root);}

		void post_order(BSTNode<T>* ptr){

			if(!ptr)
				return;

			post_order(ptr->left);
			post_order(ptr->right);
			visit(ptr);
		}

		void post_order(){post_order(root);}

		BSTNode<T>* max(){return max(root);}

		BSTNode<T>* max(BSTNode<T>* from){

			if(isEmpty())
                throw out_of_range("Empty bst...");

			BSTNode<T>* ptr = from;
			while(ptr->right)
				ptr = ptr->right;

			return ptr;
		}

		BSTNode<T>* min(){return min(root);}

		BSTNode<T>* min(BSTNode<T>* from){

			if(isEmpty())
                throw out_of_range("Empty bst...");

			BSTNode<T>* ptr = from;
			while(ptr->left)
				ptr = ptr->left;

			return ptr;
		}

        BSTNode<T>* successor(T key){

            BSTNode<T>* ptr = search(key);
            if(!ptr || ptr == min())
                throw out_of_range("...successor doesn't exist...");

            return successor(ptr);
        }

		BSTNode<T>* successor(BSTNode<T>* x){

			if(isEmpty())
				return nullptr;

			if(x->right) 
				return min(x->right);

			BSTNode<T>* y = x->parent;
			while(x && x == y->right)  //fino a che x non è un figlio sinistro
			{
				x = y;
				y = y->parent;
			}

			return y;
		}

        BSTNode<T>* predecessor(T key){

            BSTNode<T>* ptr = search(key);
            if(!ptr || ptr == min())
                throw out_of_range("...predecessor doesn't exist...");

            return predecessor(ptr);
        }

		BSTNode<T>* predecessor(BSTNode<T>* x){

			if(isEmpty())
				return nullptr;

			if(x->left)
				return max(x->left);

			BSTNode<T>* y = x->parent;
			while(x && x == y->left)  //fino a che x non è un figlio destro
			{
				x = y;
				y = y->parent;
			}
			
			return y;
		}

		BSTNode<T>* search(T key){
			if(isEmpty())
                throw out_of_range("Empty bst...");

			return search(root, key);
		}

		BSTNode<T>* search(BSTNode<T>*ptr , T key){

			if(!ptr)
				return nullptr;

			if(ptr->key == key)
				return ptr;

			if(key <= ptr->key)
				return search(ptr->left, key);

			else
				return search(ptr->right, key);
		}

		BSTNode<T>* remove(BSTNode<T>* node){ 

			//Caso 1: node è una foglia
			if(!node->left && !node->right)
			{
				if(node == node->parent->left)
					node->parent->left = nullptr;

				else if(node == node->parent->right)
					node->parent->right = nullptr;

				return node;
			}

			//Caso 2: node ha un solo figlio
			if(!node->right && node->left)
			{
				node->left->setParent(node->parent);

				if(node == node->parent->left)
					node->parent->left = node->left;

				else if(node == node->parent->right)
					node->parent->right = node->left;

				return node;
			}

			if(!node->left && node->right)
			{
				node->right->setParent(node->parent);

				if(node == node->parent->left)
					node->parent->left = node->right;

				else if(node == node->parent->right)
					node->parent->right = node->right;

				return node;
			}

			return nullptr;
		}

		BSTNode<T>* remove(T key){

			if(isEmpty()) //albero vuoto
				return nullptr;

			BSTNode<T>* node = search(key);

			if(!node)  //nodo non trovato
				return nullptr;

			BSTNode<T>* toDelete = remove(node);

			//se non sono nel terzo caso mi ritorno il valore del nodo, che ho comunque cancellato con "remove(node)"

			if(toDelete != nullptr) 
				return toDelete;

			//Caso 3 -> Voglio eliminare un nodo con due figli

			//Sostituisco il nodo da cancellare con il successore
			BSTNode<T>* next = successor(node);

			//Sostituisco la chiave
			T swap = node->key;
			node->key = next->key;
			next->key = swap;

			toDelete = remove(next); //stavolta sono sicuramente in uno dei due casi precedenti
			return toDelete;
		}

        //Below 
	    void cancel_below(BSTNode<T>* ptr, T key){
	        if(ptr->key <= key)
	            remove(ptr->key);
	    }

	    void remove_below(BSTNode<T>* ptr, T key){
	        if(!ptr)
	            return;

	        remove_below(ptr->right, key);
	        cancel_below(ptr, key);
	        remove_below(ptr->left, key);
	    }

	    void remove_below(T key){remove_below(root, key);}

	    //Above
		void visit_above(BSTNode<T>* ptr, T key){
			if(ptr->key >= key)
				cout << "\n" << *ptr ;
		}

		void print_above(BSTNode<T>* ptr, T key){
			if(!ptr)
				return;

			print_above(ptr->left, key);
			visit_above(ptr, key);
			print_above(ptr->right, key);

		}

		void print_above(T key){print_above(root, key);}


};

#endif