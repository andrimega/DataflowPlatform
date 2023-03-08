#include <omnetpp.h>

using namespace omnetpp;

class Worker: public cSimpleModule{
    /*
    Workers are either mappers or reducers.
    
    SharedAttributes: int workerID; boolean failed; int failureProbability; boolean executing.
    SharedProcedures: pingPong, if a ping is recieved it responds with a pong.

    messages:
        Ping();
        Pong(workerId);


    Messages:
    Execute Task: recieves from the coordinator the message to execute a task, the worker accesses the data in the global structure corresponding to its index and executes the task. The result is also saved to the global structure. After execution a timer is set for a executionTime selfmessage.
    Execution Time: the task is finished and a completion message can be sent out to the coordinator.

    If a stopExecuting message is recieved stop the current task.

    Failure model:
    randomly fail after recieving an execute task message. Set the failed flag to true and set a timer for a Recovery self message.
    after recieving the recovery send a backonline to coordinator

    messages:
        executeTask();
        executionTime();
        completion(workerId);
        Ping();
        Pong(workerId);
        Recovery();
        backOnline(workerId);
        stopExecution()

    data structures:
        GlobalData[] data;
        id of the worker;
        bool to know if the worker has failed

    technically the coordinator cannot schedule on a failed worker so the flag is not needed, this way it is more general
    */
}

class Mapper{
    /*
    recieves the map from the coordinator with a defineMap message and saves the list of instructions, recieves the GlobalData structure. Recieves the executeTask message from the coordinator and fails with an x% chance. If it fails then its failed flag becomes true and set a timer for a Recovery self message, after recieveing the flag becomes false and a backonline message is sent to the coordinator. If it does not fail then the task is executed and an executionTime selfmessage is schedules, in the meanwhile every message recieved is delayed and the flag executing is set.
    After the executionTime is recieved the computation is completed, the mapper saves the output locally, performs the shuffle and adds a terminator pair, then computes using mod the reducers it will have to send keys to and send them a getPairs. The mapper also sends a mapCompletion to the coordinator.
    if a resendKey message is recieved the pairs for a reducer are sent again.

    Messages:
        defineMap(Map*);
        setData(GlobalData*);
        executeTask(int index);
        Recovery();
        backOnline(workerId);
        executionTime();
        getPairs(OutputPairs*, int taskIndex);
        Mapcompletion(workerId);
        resendKey(int reducerID);
        
    Config Data:
        int numberOfReducers;

    data structures:
        Map;
        GlobalData[] data;
        OutputPairs;

    */
}

class Reducer{
    /*
    recieves from the coordinator a setReduce message.
    recieves from the mapper the getPairs message and starts retrieving the pairs that belong to it, after the terminator pais is read and saved the index of the task is set as fully read in tasksRead.
    the reducer initiates the reduce task and randomly fails. If it does not fail then it schedules an executionTime selfmessage and performs the reduce, in the meanwhile the executing flag is set. If it fails then its failed flag becomes true and set a timer for a Recovery self message, after recieveing the flag becomes false and a backonline message is sent to the coordinator.
    if a taskDone is recieved the output is written and the computation ends.
    if a getPairs is recieved for a task already read the reducer skips them.

    messages:
        setReduce(Reduce*);
        getPairs(OutputPairs*, int taskIndex);

    data structures:
        reduce;
        pairs;
        tasksRead;
    */
}
