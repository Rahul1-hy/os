import threading
import queue
import time
import random

BUFFER_SIZE = 5
NUM_PRODUCERS = 2
NUM_CONSUMERS = 3

buffer = queue.Queue(maxsize=BUFFER_SIZE)
mutex = threading.Semaphore(1)
empty = threading.Semaphore(BUFFER_SIZE)
full = threading.Semaphore(0)

def producer(thread_id):
    for _ in range(5):  # Produce 5 items
        item = random.randint(0, 99)  # Generate a random item

        empty.acquire()
        mutex.acquire()

        # Critical section: Add item to the buffer
        buffer.put(item)
        print(f"Producer {thread_id} produced item {item}")

        mutex.release()
        full.release()  # Notify a waiting consumer

        time.sleep(1)  # Simulating production time

def consumer(thread_id):
    for _ in range(5):  # Consume 5 items
        full.acquire()
        mutex.acquire()

        # Critical section: Remove item from the buffer
        item = buffer.get()
        print(f"Consumer {thread_id} consumed item {item}")

        mutex.release()
        empty.release()  # Notify a waiting producer

        time.sleep(2)  # Simulating consumption time

def main():
    producer_threads = []
    consumer_threads = []

    # Creating producer threads
    for i in range(NUM_PRODUCERS):
        producer_threads.append(threading.Thread(target=producer, args=(i,)))

    # Creating consumer threads
    for i in range(NUM_CONSUMERS):
        consumer_threads.append(threading.Thread(target=consumer, args=(i,)))

    # Starting producer threads
    for thread in producer_threads:
        thread.start()

    # Starting consumer threads
    for thread in consumer_threads:
        thread.start()

    # Joining producer threads
    for thread in producer_threads:
        thread.join()

    # Joining consumer threads
    for thread in consumer_threads:
        thread.join()

if __name__ == "__main__":
    main()
