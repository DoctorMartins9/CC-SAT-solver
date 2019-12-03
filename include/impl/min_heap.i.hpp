
namespace hp { 

    template<typename T>
    void MinHeap<T>::heapify(std::vector<Node<T>> &heap, uint64_t n, uint64_t i) {
        
        uint64_t smallest = i; 
        uint64_t l = 2*i + 1; 
        uint64_t r = 2*i + 2;
    
        if (l < n && heap[l].getValue() < heap[smallest].getValue()) 
            smallest = l; 
    
        if (r < n && heap[r].getValue() < heap[smallest].getValue()) 
            smallest = r;

        if (smallest != i) { 
            Node<T> temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            
            heapify(heap, n, smallest); 
        } 
    }

    template<typename T>
    void MinHeap<T>::minHeapify(){
        for (int i = ( size() / 2 ) - 1 ; i >= 0 ; i--)
            heapify(heap , size() , i);
    }

    
    template<typename T>
    MinHeap<T>::MinHeap(std::vector<T>& input) : Heap<T>(input) {
        minHeapify();
    }

    // Add an element in heap and then re-order
    template<typename T>
    void MinHeap<T>::addElement(T n){
        Heap<T>::addElement(n);
        minHeapify();
    }

    template<typename T>
    void MinHeap<T>::erase(uint64_t index) {
        heap.erase(heap.begin() + index);
        minHeapify();
    }

    template<typename T>
    void MinHeap<T>::eraseByValue(T value) {

        for(uint64_t i = 0 ; i < size() ; i++)
            if(heap[i].getValue() == value ){
                heap.erase(heap.begin() + i);
                i = -1;
            }
        minHeapify();
    }

    template<typename T>
    void MinHeap<T>::addVector(std::vector<T> &vec) {
        
        for(uint64_t i = 0; i < vec.size() ; i++ )
            addElement(vec[i]);
        
    }

    template<typename T>
    MinHeap<T> MinHeap<T>::operator+(Heap<T> &input) {
        auto s = input.getVector();
        auto p = getVector();

        s.insert(s.end(), p.begin(), p.end());


        return MinHeap(s);
    }
        
}   // namespace 'hp'
