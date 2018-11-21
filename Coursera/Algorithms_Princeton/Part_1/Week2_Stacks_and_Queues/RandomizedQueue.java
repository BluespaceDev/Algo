import edu.princeton.cs.algs4.StdRandom;

import java.util.Iterator;

public class RandomizedQueue<Item> implements Iterable<Item> {

    private class ItemIterator implements Iterator<Item> {

        private int i;
        private int[] randomIndices;

        public ItemIterator() {
            i = 0;
            randomIndices = new int[size()];
            for (int j = 0; j < size(); j++) {
                randomIndices[j] = j;
            }
            StdRandom.shuffle(randomIndices);
        }

        @Override
        public boolean hasNext() {
            return i < size();
        }

        @Override
        public Item next() {
            if (!hasNext()) throw new java.util.NoSuchElementException();
            return items[randomIndices[i++]];
        }

        @Override
        public void remove() {
            throw new java.lang.UnsupportedOperationException();
        }
    }

    private Item[] items;
    private int sizeOfItems;

    public RandomizedQueue()                 // construct an empty randomized queue
    {
        items = (Item[]) new Object[2];
        sizeOfItems = 0;
    }

    public boolean isEmpty()                 // is the randomized queue empty?
    {
        return size() == 0;
    }

    public int size()                        // return the number of items on the randomized queue
    {
        return sizeOfItems;
    }

    public void enqueue(Item item)           // add the item
    {
        if (item == null) throw new java.lang.IllegalArgumentException();

        if (items.length == size()) resize(items.length << 1);

        items[sizeOfItems++] = item;
    }

    public Item dequeue()                    // remove and return a random item
    {
        if (isEmpty()) throw new java.util.NoSuchElementException();

        if (items.length == size() << 2) resize(items.length >> 1);

        int i = StdRandom.uniform(size());
        Item ret = items[i];
        items[i] = items[--sizeOfItems];
        items[sizeOfItems] = null;  // to prevent loitering
        return ret;
    }

    public Item sample()                     // return a random item (but do not remove it)
    {
        if (isEmpty()) throw new java.util.NoSuchElementException();
        return items[StdRandom.uniform(size())];
    }

    public Iterator<Item> iterator()         // return an independent iterator over items in random order
    {
        return new ItemIterator();
    }

    private void resize(int capacity) {
        Item[] temp = (Item[]) new Object[capacity];
        for (int i = 0; i < size(); i++) {
            temp[i] = items[i];
        }
        items = temp;
    }

    public static void main(String[] args)   // unit testing (optional)
    {
        RandomizedQueue<Integer> queue = new RandomizedQueue<>();
        for (int i = 0; i < 10; i++) {
            queue.enqueue(i);
        }
        System.out.println(queue.size());
        for (Integer i : queue) {
            System.out.println(i);
        }
        System.out.println("sample:" + queue.sample());
        System.out.println("dequeue");
        while (!queue.isEmpty()) System.out.println(queue.dequeue());
        System.out.println(queue.size());
    }
}
