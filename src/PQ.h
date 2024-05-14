#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>

template <class T>
class MutablePriorityQueue {
    std::vector<T*> H;
    /**
     * @brief Auxiliar function for priority queue used in prim algorithm
     */
    void heapifyUp(unsigned i);
    /**
     * @brief Auxiliar function for priority queue used in prim algorithm
     */
    void heapifyDown(unsigned i);

    /**
     * @brief Auxiliar function for priority queue used in prim algorithm
     * @param i Index of the element to be set
     * @param x Element to be set
     */
    inline void set(unsigned i, T* x);
public:
    /**
     * @brief Construct a new Mutable Priority Queue object
     */
    MutablePriorityQueue();
    /**
     * @brief Insert a new element in the priority queue
     * @param x Element to be inserted
     */
    void insert(T* x);
    /**
     * @brief Extract the minimum element from the priority queue
     * @return T* Minimum element
     */
    T* extractMin();
    /**
     * @brief Decrease the key of an element in the priority queue
     * @param x Element to decrease the key
     */
    void decreaseKey(T* x);
    /**
     * @brief Check if the priority queue is empty
     * @return true if the priority queue is empty, false otherwise
     */
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if (H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size() - 1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k + 1 < H.size() && *H[k + 1] < *H[k])
            ++k; // right child of i
        if (!(*H[k] < *x))
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T* x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif
