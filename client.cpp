/*
    Original author of the starter code
    Tanzir Ahmed
    Department of Computer Science & Engineering
    Texas A&M University
    Date: 2/8/20


    Please include your Name, UIN, and the date below
    Name: Blake Burton
    UIN: 832005261
    Date: 9/8/24
*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>


#include <iostream>
#include <fstream>
#include <sstream>


#include "common.h"
#include "FIFORequestChannel.h"


using namespace std;


/* Verifies if the commandline argument passed to client.cpp "num_of_servers"
   is one of the following numbers (2,4,8,16). */
/*void verify_server_count(int num_of_servers)
{
   
        TODO: Allow only 2, 4, 8 or 16 servers
        If the number of servers is any other number
        Print "There can only be 2, 4, 8 or 16 servers\n"
        In the next line, print "Exiting Now!\n"
   
}*/


/* Establishes a new channel with the server by sending appropriate NEWCHANNEL_MSG message.
   Sets this new channel as main channel (point chan to new channel) for communication with the server. */
/*void set_new_channel(FIFORequestChannel *chan, FIFORequestChannel **channels, int buffersize)
{
    channels[0] = nullptr;


      TODO:
        1)request new channel
          Hint: use cwrite and cread


        2)open channel on client side


        3)set the above channel as the main channel


        Remember to clean up any object you allocated memory to
   
}
*/
/* Send datamsg request to server using "chan" FIFO Channel and
   cout the response with serverID */
/*void req_single_data_point(FIFORequestChannel *chan,
                           int person,
                           double time,
                           int ecg)
{
   
        TODO: Reading a single data point
        Hint: Go through datamsg and serverresponse classes
        1) sending a data msg
            Hint: use cwrite


        2) receiving response
            Hint: use cread
   


    // Don't Change the cout format present below
    //  cout << resp.ecgData <<" data on server:"<< resp.serverId << " on channel " << chan->name() << endl << endl;
}*/


/* Sends 1000 datamsg requests to one server through FIFO Channel and
   dumps the data to x1.csv regardless of the patient ID */
/*void req_multiple_data_points(FIFORequestChannel *chan,
                              int person,
                              double time,
                              int ecg)
{
    // TODO: open file "x1.csv" in received directory using ofstream
    ofstream myfile;


    // set-up timing for collection
    timeval t;
    gettimeofday(&t, nullptr);
    double t1 = (1.0e6 * t.tv_sec) + t.tv_usec;


    // requesting data points
    // NOTE: Each data point is represented in `time (s), ecg1, ecg2`
    //       starting from t=0 (s), the time interval between data point is 4 ms
    // TODO: Receive 1000 data points, starting from t=4 (s).




    // E.g. myfile << time << "," << ecg1 << "," << ecg2 << flush;




    // compute time taken to collect
    gettimeofday(&t, nullptr);
    double t2 = (1.0e6 * t.tv_sec) + t.tv_usec;


    // display time taken to collect
    cout << "Time taken to collect 1000 datapoints :: " << ((t2 - t1) / 1.0e6) << " seconds on channel " << chan->name() << endl;


    // closing file
}*/


/* Request Server to send contents of file (could be .csv or any other format) over FIFOChannel and
   dump it to a file in recieved folder */
/*void transfer_file(FIFORequestChannel *chan,
                   string filename,
                   int buffersize)
{
    // sending a file msg to get length of file
    // create a filemsg, buf, and use cwrite to write the message


    // receiving response, i.e., the length of the file
    // Hint: use cread


    // opening file to receive into


    // set-up timing for transfer
    timeval t;
    gettimeofday(&t, nullptr);
    double t1 = (1.0e6 * t.tv_sec) + t.tv_usec;


    // requesting file
    // TODO: Create a filemsg with the current offset you want
    // to read from. Receive data from the server.


    // compute time taken to transfer
    gettimeofday(&t, nullptr);
    double t2 = (1.0e6 * t.tv_sec) + t.tv_usec;


    // display time taken to transfer
    cout << "Time taken to transfer file :: " << ((t2 - t1) / 1.0e6) << " seconds" << endl
         << endl;


    // closing file
}
*/


//int argc, char *argv[]
//goes in main below
// |
// |
// v
//int main(int argc, char *argv[])


int main(int argc, char *argv[])
{
    int person = -1;
    double time = -1;
    int ecg = -1;


    int buffersize = MAX_MESSAGE;


    string filename = "";


    bool new_chan = false;


    int num_of_servers = 2;


    int opt;
    while ((opt = getopt(argc, argv, "p:t:e:m:f:s:c")) != -1)
    {
        switch (opt)
        {
        case 'p':
            person = atoi(optarg);
            break;
        case 't':
            time = atof(optarg);
            break;
        case 'e':
            ecg = atoi(optarg);
            break;
        case 'm':
            buffersize = atoi(optarg);
            break;
        case 'f':
            filename = optarg;
            break;
        case 's':
            num_of_servers = atoi(optarg);
            break;
        case 'c':
            new_chan = true;
            break;
        }
    }


        if (person == 0 || time == 0 || ecg == 0 || buffersize == 0 || new_chan == false) {
            std::cout << "\n";
        }


    /*
        Example Code Snippet for reference, you can delete after you understood the basic functionality.
    */


        //char *file_name = "server";
        //char *const yes = "/programming-assignment-1-Burton877368-4/server";


        /*const char* args[] = {"/programming-assignment-1-Burton877368-4/server", "-s 4", NULL};


        long cpid1, cpid2;
       
        switch(cpid1 = fork()) {
            case -1:
                perror("fork failed");
                return EXIT_FAILURE;


            case 0:
                std::cout << "First child, pid= " << getpid() << "\n";
                execvp("server", (char* const*)args);
        }


        wait(NULL);
        switch(cpid2 = fork()) {
            case -1:
                perror("fork failed");
                return EXIT_FAILURE;


            case 0:
                std::cout << "Second child, pid= " << getpid() << "\n";
                execvp("server", (char* const*)args);
        }
       
        while (wait(NULL) != -1);*/


            pid_t parent = getpid();


        if (!(num_of_servers == 2 || num_of_servers == 4 || num_of_servers == 8 || num_of_servers == 16)) {
            throw std::runtime_error("Error: Inappropriate server amount");
        }
       


            for (int i = 0; i < num_of_servers; ++i) {
               
                if (getpid() == parent) {
                    fork();
                }


                if (getpid() != parent) {
                    char* args[] = {(char*)"./server", (char*)"-m", (char*)to_string(buffersize).c_str(), (char*)"-s", (char*)to_string(i + 1).c_str(), NULL};


                    execvp(args[0], args);
                    exit(0);
                }


               
            }


            if (getpid() == parent) {          


                //person = 1;

                /*FIFORequestChannel* chan1 = new FIFORequestChannel("control_1_", FIFORequestChannel::CLIENT_SIDE);
                FIFORequestChannel* chan2 = new FIFORequestChannel("control_2_", FIFORequestChannel::CLIENT_SIDE);

                if (num_of_servers >= 4) {
                    FIFORequestChannel* chan3 = new FIFORequestChannel("control_3_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan4 = new FIFORequestChannel("control_4_", FIFORequestChannel::CLIENT_SIDE);
                }
                if (num_of_servers > 8) {
                    FIFORequestChannel* chan5 = new FIFORequestChannel("control_5_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan6 = new FIFORequestChannel("control_6_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan7 = new FIFORequestChannel("control_7_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan8 = new FIFORequestChannel("control_8_", FIFORequestChannel::CLIENT_SIDE);
                }
                if (num_of_servers > 16) {
                    FIFORequestChannel* chan9 = new FIFORequestChannel("control_9_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan10 = new FIFORequestChannel("control_10_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan11 = new FIFORequestChannel("control_11_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan12 = new FIFORequestChannel("control_12_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan13 = new FIFORequestChannel("control_13_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan14 = new FIFORequestChannel("control_14_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan15 = new FIFORequestChannel("control_15_", FIFORequestChannel::CLIENT_SIDE);
                    FIFORequestChannel* chan16 = new FIFORequestChannel("control_16_", FIFORequestChannel::CLIENT_SIDE);
                }*/
                
                int switch_value = ceil(person/(16/num_of_servers)) + 1;
                
                FIFORequestChannel chan("control_" + to_string(switch_value) + "_", FIFORequestChannel::CLIENT_SIDE);

                //cout << ("control_" + to_string(switch_value) + "_") << "\n";
                
                //cout << switch_value << "\n";


                /*switch(switch_value) {
                    case(1):
                        chan = chan1;
                        return 0;
                    case(2):
                        chan = chan2;
                        return 0;
                    case(3):
                        chan = chan3;
                        return 0;
                    case(4):
                        chan = chan4;
                        return 0;
                }*/
           
           
           


                //single data, only if p,t,e != -1
                // example data point request
               

                if (person != -1 && time != -1  && ecg != -1) {
                    char buf[MAX_MESSAGE]; // 256
                    datamsg x(person, time, ecg);


                    memcpy(buf, &x, sizeof(datamsg));
                    chan.cwrite(buf, sizeof(datamsg)); // question


                    serverresponse resp(-1,-1);
                    chan.cread(&resp, sizeof(serverresponse)); //answer


                    cout << resp.ecgData <<" data on server:"<< resp.serverId << " on channel " << chan.name() << endl << endl;
                } else if (person != -1) {
                    char buf[MAX_MESSAGE]; // 256

                    time = 4;
                    ecg = 1;

                    datamsg x(person, time, ecg);

                    ofstream file;
                    file.open("./received/x1.csv");
                    
                    for (int i = 0; i < 1000; ++i) {
                        x.ecgno = 1;
                        memcpy(buf, &x, sizeof(datamsg));
                        chan.cwrite(buf, sizeof(datamsg));

                        serverresponse resp1(-1,-1);
                        chan.cread(&resp1, sizeof(serverresponse));

                        x.ecgno = 2;                        
                        memcpy(buf, &x, sizeof(datamsg));
                        chan.cwrite(buf, sizeof(datamsg));

                        serverresponse resp2(-1,-1);
                        chan.cread(&resp2, sizeof(serverresponse));

                        file << x.seconds << "," << resp1.ecgData << "," << resp2.ecgData << "\n";
                        x.seconds += 0.004;
                    }

                    file.close();
                }

                MESSAGE_TYPE quit_message = QUIT_MSG;
               
                /*chan1->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                chan2->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                
                delete chan1;
                delete chan2;
                

                if (num_of_servers >= 4) {
                    chan3->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan4->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    delete chan3;
                    delete chan4;
                }
                if (num_of_servers > 8) {
                    chan5->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan6->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan7->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan8->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    delete chan5;
                    delete chan6;
                    delete chan7;
                    delete chan8;
                }
                if (num_of_servers > 16) {
                    chan9->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan10->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan11->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan12->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan13->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan14->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan15->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    chan16->cwrite(&quit_message, sizeof(MESSAGE_TYPE));
                    delete chan9;
                    delete chan10;
                    delete chan11;
                    delete chan12;
                    delete chan13;
                    delete chan14;
                    delete chan15;
                    delete chan16;
                }*/
                chan.cwrite(&quit_message, sizeof(MESSAGE_TYPE));

                wait(NULL);
            }


        // Else, if p != -1 request 1000
        // Loop over 100 lines
        // send request for ecg 1
        // send request of ecg 2
        // write line to recieved/x1.csv


        // sending a non-sense message, you need to change this
        /*filemsg fm(0, 0);
        string fname = "teslkansdlkjflasjdf.dat";


        int len = sizeof(filemsg) + (fname.size() + 1);
        char* buf2 = new char[len];
        memcpy(buf2, &fm, sizeof(filemsg));
        strcpy(buf2 + sizeof(filemsg), fname.c_str());
        chan.cwrite(buf2, len);  // I want the file length;


        delete[] buf2;


        // closing the channel
        MESSAGE_TYPE m = QUIT_MSG;
        chan.cwrite(&m, sizeof(MESSAGE_TYPE));
        */
   


    //verify_server_count(num_of_servers);


    //bool data = ((person != 0) && (time != 0.0) && (ecg != 0));
    //bool file = (filename != "");
    // Initialize FIFORequestChannel channels.
    // What should be the size of the object?
    // HINT: We need n channels(one for each of the servers) plus one more for new datachannel request.


    // fork to create servers


    // open all requested channels


    // Initialize step and serverId


    /*if (!filename.empty())
    {
        string patient = filename.substr(0, filename.find('.'));
        std::istringstream ss(patient);
        //int patient_id;
        // If ss has a patient id, set serverId using ceil again
        // else, use the first server for file transfer
    }


    // By this line, you should have picked a server channel to which you can send requests to.


    // TODO: Create pointer for all channels


    if (new_chan)
    {
        // call set_new_channel
    }*/


    // request a single data point
    /*if (data)
    {
        // call req_single_data_point
    }


    // request a 1000 data points for a person
    if (!data && person != 0)
    {
        // call req_multiple_data_points
    }*/


    // transfer a file
    //if (file)
    //{
        // call transfer_file
    //}


    // close the data channel
    // if new_chan has any value, cwrite with channels[0]


    // close and delete control channels for all servers


    // wait for child to close


}
