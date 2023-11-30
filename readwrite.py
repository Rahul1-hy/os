import threading
import time

class ReaderWriterProblem:
    def __init__(self):
        self.readers = 0
        self.mutex = threading.Semaphore(1)
        self.write_lock = threading.Semaphore(1)

    def reader(self, thread_id):
        self.mutex.acquire()
        self.readers += 1
        if self.readers == 1:
            self.write_lock.acquire()
        self.mutex.release()

        # Reading
        print(f"Reader {thread_id} is reading.")
        time.sleep(1)  # Simulating reading time

        self.mutex.acquire()
        self.readers -= 1
        if self.readers == 0:
            self.write_lock.release()
        self.mutex.release()

    def writer(self, thread_id):
        self.write_lock.acquire()

        # Writing
        print(f"Writer {thread_id} is writing.")
        time.sleep(2)  # Simulating writing time

        self.write_lock.release()

def main():
    rw_problem = ReaderWriterProblem()

    def run_reader(thread_id):
        for _ in range(3):  # Readers read 3 times
            rw_problem.reader(thread_id)

    def run_writer(thread_id):
        for _ in range(2):  # Writers write 2 times
            rw_problem.writer(thread_id)

    # Creating reader and writer threads
    reader_threads = [threading.Thread(target=run_reader, args=(i,)) for i in range(3)]
    writer_threads = [threading.Thread(target=run_writer, args=(i,)) for i in range(2)]

    # Starting threads
    for thread in reader_threads + writer_threads:
        thread.start()

    # Waiting for all threads to finish
    for thread in reader_threads + writer_threads:
        thread.join()

if __name__ == "__main__":
    main()
