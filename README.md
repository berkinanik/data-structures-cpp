# data-structures-cpp
This is a repository for my data structures course assignments I completed during the course of METU EE441 Data Structures in 2021-2022 Fall Semester.

There are three cpp console applications. I created the projects and did development using [Code::Blocks IDE](https://www.codeblocks.org/downloads/). Their Code::Blocks project files (*``cbp``*) are in the folders also.

# Assignment Requirements and Instructions
*These assignments' instructions credits to [**Middle East Technical University - Electrical - Electronics Engineering Department**](https://eee.metu.edu.tr/) and [**EE441 - Data Structures Course Lecturers**](https://catalog.metu.edu.tr/course.php?course_code=5670441).*

# Assignment 1
## Introduction
You are asked to implement a user interface and the corresponding database of students for ‘EE441’ course. The database entries will be instances of a custom-made Student class. The database itself will be an instance of a Course class. Student and Course classes and the user interface for the ‘EE441’ course will be designed and implemented in this homework.

## Required Data Structures
### Student Class
Student class consists of the following;

- Private members:
  - ID
  - name
  - surname
  - quiz_scores (an array for 1st, 2nd, 3rd and 4th quiz scores)
  - hw_scores (an array for 1st, 2nd and 3rd homework scores)
  - final_score (final exam score)
- Public methods:
  - Constructor
  - Getter and setter methods for all members (e.g. getID, setQuizScores, etc.)
  - overallCourseScore (calculates overall score of a student considering quiz, homework and final exam scores and weights)

### Course Class
Course class consists of the following;
- Private members:
  - students[MAX_SIZE] (an array for Student instances, MAX_SIZE is 10)
  - num (the current number of students in EE441 course)
  - exam weights
    - weightQ (weight for the quizzes, default 30%)
    - weightHW (weight for the homeworks, default 30%)
    - weightF (weight for the final exam, default 40%)
- Public methods:
  - Constructor
  - getNum (returns how many students are in the course)
  - addNewStudent (adds new student to the course)
  - updateWeights (updates weights)
  - getStudentInfo (returns a Student information given an ID)
  - calculateAverage (calculates course averages for quiz, homework, final exam and overall course scores)

## User Interface
The program should ask the user for his/her input by offering only the following options as a menu:

1. Add student
2. Search a student by ID
3. Change a student’s score
4. Update weights
5. Show classroom average
6. Show students with overall score above a threshold
7. Show students with overall score below a threshold
8. Exit


# Assignment 2

## Introduction
As a teaching assistant, your first task of the semester is to divide students into three laboratory sections: Wednesday, Thursday, and Friday each of which has limited capacity. Since students have different course schedules, assigning them randomly is not an option. Therefore, you have asked them to submit their preferences based on which you can assign them to the eligible sections. However, there are an exponential number of ways to assign students and it is not easy to know which one is the best. To choose the best one, you have decided to code some of them and make your computer do all the work to finish the task as fast as possible. Now, you are going to implement your first grouping algorithm by using class, stack, and queue data structures.

### Input File Format
- The name of the input file will be 'preferences.txt'.
- The first 3 lines must be reserved for section capacity. The order of the ections is random.
- The remaining lines should start with student ID and continue with section references, all separated by a comma.
- Students will have at least 1 preference.
- The section written right after the student ID has the highest priority for hat student and the last section has the lowest one.
- Capital letters W, T, F will be used for section days Wednesday, Thursday, and Friday, respectively.

### Output File Format
- The name of the output file will be 'results.txt'.
- Students assigned to a section will be shown by their student IDs under the name of that section day.
- Students who have not been assigned to any section will be indicated by their student IDs under 'Unassigned'. If all students have been assigned, just write '-'.

## Required Data Structures
### Student Class:
- You are going to implement a "Student" class which will be used to store & access related information about students such as student ID and preferences.
- When a new student is received i.e., a line is read from the input file, a new "Student" object must be created.
- It must be able to return the number of eligible sections for a student by taking into consideration the fullness of the sections.
- It must be able to return the most preferred section of a student that is not full.
- Any other feature you think necessary to use in your design...

### "Section" Stack:
- You are going to implement a "Section" stack to store "Student" objects.
- You will use one "Section" stack for each section i.e., three stacks in total.
- When a student is assigned to a section, their "Student" object will be pushed into the corresponding "Section" stack.
- The maximum number of "Student" objects that a "Section" stack can hold is given in the input file as section capacity.
- It must be able to indicate if it is full or not.
- Any other feature you think necessary to use in your design...
### "Waiting" Queue:
- You are going to implement a "Waiting" queue to store "Student" objects.
- You will use only one "Waiting" queue.
- When a student is not assigned to any section, s/he will be put in the "Waiting" queue and will wait to be placed in later steps.
- Any other feature you think necessary to use in your design...


# Assignment 3

## Introduction
A single core CPU can typically run a single process at a time. However, computers are required to run several processes concurrently, e.g. a web browser, a word processor and a printer spooler. Due to the architecture of CPU, such processes have to run sequentially. Deciding which process runs at a certain time instant is one of the main tasks of operating systems, known as ‘process scheduling’.
The process scheduler keeps a data structure to hold the processes that will be executed, which is known as the ‘Ready Queue (RQ)’. When the user starts a new process, the process is inserted into the RQ according its priority. The RQ stores the processes in decreasing priority order such that the highest priority process is always at the front of the RQ. When CPU is ready, the process scheduler selects the next process to execute as the process at the front of the RQ. When the CPU finishes the execution, the process is deleted from RQ. Then, the scheduler selects the next process to be executed from the RQ.
In this homework, you are asked to implement a simple OS process scheduler.

## Data Representation
For simplicity, the processes you will consider will be represented as four positive integers, processID, arrivalTime, runTime and priority. arrivalTime describes the time instant at which the process arrives. runTime describes the clock cycles required to execute the process. When a process finishes execution, your code will print its processID to the console. priority is defined similar to the practical applications such that a smaller value indicates a higher priority.
## Running Your program
Your program is required to read the process list from a text file, processes.txt, which will be in the same directory as your executable. The first line of the file contains an integer, numProcesses, that is the number of processes in the file. The following numProcesses lines contain four space separated integers, processID, arrivalTime, runTime, priority, the parameters of the corresponding process. You can assume that the processes are sorted by their arrivalTime. A sample processes.txt file is distributed with the homework. You might use Code1 to read processes into an array.
A pseudocode for the process scheduler is given in Code2. Your task is to convert this pseudocode into valid C++ and implement the classes and member functions your code requires.

## Two Different Scheduler Implementations and Comparing Their Performance
You will implement the scheduler using two different data structures to store RQ: Linked List and Binary Search Tree (BST). You will evaluate these two schedulers’ performances by comparing the total number of nodes visited to insert all arrived processes into RQ (insertion), the total number of nodes visited to find the next processes from RQ (search) and the total number of nodes visited to delete the executed processes from RQ (deletion).
### Linked List Scheduler
In this part, you are going to implement the scheduler explained above using a Linked List to keep RQ. The nodes should be kept sorted in descending order of priority. Insertion of new processes must confirm to the priority order.
### Binary Search Tree Scheduler
In this part, you are going to implement the scheduler explained above using a Binary Search Tree to keep RQ. The tree does not have to be balanced.

## Remarks for Performance Evaluation
- Use the sample input/output data in sampleData.zip to evaluate your algorithm’s performance
- processesN.txt (N=100, 500, 1000) files are sample inputs with numProcesses =N processes
- Copy processesN.txt files, one file at a time, to your project directory, rename it as processes.txt and run both linked list and binary search tree scheduler codes
- sampleOutputN_X.txt file is the expected output for the input processesN.txt using X data structure for RQ (X=linked list, binary search tree)
- Your algorithm's performance results might be slightly different from sample output. Process execution order should not.
- You don't need to save your outputs as text files. However, you do need to run your code on sample inputs and briefly comment on your results, either in a separate text file or in your main.cpp
