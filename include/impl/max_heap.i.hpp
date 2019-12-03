
namespace hp { 

    template<typename T>
    void MaxHeap<T>::heapify(std::vector<Node<T>> &heap, uint64_t n, uint64_t i) {
        
        uint64_t largest = i; 
        uint64_t l = 2*i + 1; 
        uint64_t r = 2*i + 2;
    
        if (l < n && heap[l].getValue() > heap[largest].getValue()) 
            largest = l; 
    
        if (r < n && heap[r].getValue() > heap[largest].getValue()) 
            largest = r;

        if (largest != i) { 
            Node<T> temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            
            heapify(heap, n, largest); 
        } 
    }

    template<typename T>
    void MaxHeap<T>::maxHeapify(){
        
        for (int i = ( size() / 2 ) - 1 ; i >= 0 ; i--)
            heapify(heap , size() , i);
    
    }

    template<typename T>
    void MaxHeap<T>::heapSort(std::vector<T> &vec){ 
        std::vector<T> res;
        uint64_t size = vec.size();
        res.reserve(size);
        MaxHeap mh = MaxHeap(vec);
        for(uint64_t i = 0; i < size; i++){
            
            res.insert(res.end() -i, mh[0]);
            mh.erase(0);
        }

        vec = res; 

    } 
    
    template<typename T>
    MaxHeap<T>::MaxHeap(std::vector<T>& input) : Heap<T>(input) {
        maxHeapify();
    }

    // Add an element in heap and then re-order
    template<typename T>
    void MaxHeap<T>::addElement(T n){
        Heap<T>::addElement(n);
        maxHeapify();
    }

    template<typename T>
    void MaxHeap<T>::erase(uint64_t index) {
        heap.erase(heap.begin() + index);
        maxHeapify();
    }

    template<typename T>
    void MaxHeap<T>::eraseByValue(T value) {
        for(uint64_t i = 0 ; i < size() ; i++)
            if(heap[i].getValue() == value ){
                heap.erase(heap.begin() + i);
                i = -1;
            }
        maxHeapify();
    }

    template<typename T>
    void MaxHeap<T>::addVector(std::vector<T> &vec) {    
        for(uint64_t i = 0; i < vec.size() ; i++ )
            addElement(vec[i]);
        
    }

    template<typename T>
    MaxHeap<T> MaxHeap<T>::operator+(Heap<T> &input) {
        auto s = input.getVector();
        auto p = getVector();
        s.insert(s.end(), p.begin(), p.end());
        return MaxHeap(s);
    }

}   // namespace 'hp'
