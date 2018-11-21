import java.util.Iterator;

public class Deque<Item> implements Iterable<Item> {

    private class Node {
        private Node prev;
        private Node next;
        private Item item;
    }

    private class NodeIterator implements Iterator<Item> {

        Node current = first;

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public Item next() {
            if (current == null) throw new java.util.NoSuchElementException();

            Item item = current.item;
            current = current.next;
            return item;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    private Node first, last;
    private int sizeOfItems;


    public Deque()                           // construct an empty deque
    {
        sizeOfItems = 0;
    }

    public boolean isEmpty()                 // is the deque empty?
    {
        return size() == 0;
    }

    public int size()                        // return the number of items on the deque
    {
        return sizeOfItems;
    }

    public void addFirst(Item item)          // add the item to the front
    {
        if (item == null) throw new java.lang.IllegalArgumentException();

        Node node = new Node();
        node.prev = null;
        node.next = first;
        node.item = item;

        first = node;

        if (isEmpty()) last = first;
        else first.next.prev = first;

        ++sizeOfItems;
    }

    public void addLast(Item item)           // add the item to the end
    {
        if (item == null) throw new java.lang.IllegalArgumentException();

        Node node = new Node();
        node.prev = last;
        node.next = null;
        node.item = item;

        last = node;

        if (isEmpty()) first = last;
        else last.prev.next = last;

        ++sizeOfItems;
    }

    public Item removeFirst()                // remove and return the item from the front
    {
        if (isEmpty()) throw new java.util.NoSuchElementException();

        Item ret = first.item;

        --sizeOfItems;

        if (isEmpty()) {
            first = null;
            last = null;
        } else {
            first = first.next;
            first.prev = null;
        }

        return ret;
    }


    public Item removeLast()                 // remove and return the item from the end
    {
        if (isEmpty()) throw new java.util.NoSuchElementException();

        Item ret = last.item;

        --sizeOfItems;

        if (isEmpty()) {
            first = null;
            last = null;
        } else {
            last = last.prev;
            last.next = null;
        }

        return ret;
    }

    public Iterator<Item> iterator()         // return an iterator over items in order from front to end
    {
        return new NodeIterator();
    }

    public static void main(String[] args)   // unit testing (optional)
    {
        Deque<Integer> deque = new Deque<>();
        deque.addFirst(1);
        deque.removeLast();
        System.out.println(deque.isEmpty());
    }
}
