#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#include "int_node.h"
#include "bplus_roots.h"
#include "timestamp.h"
#include "file_count.h"
#include "message.h"
#include "user.h"
#include "state.h"

int main(int argc, char **argv)
{
    // time the program
    struct timeval sysTimeStart, sysTimeEnd;
    gettimeofday(&sysTimeStart, NULL);

    // get file counts
    file_count_t *fc = read_file_count();
    int messageCount = fc->messages;
	int timestampCount = fc->timestamps;
    int userCount = fc->users;
    free_file_count(fc);
    
    // get b+ roots
    bplus_roots_t *bpr = read_bplus_roots();
    int stateRoot = bpr->state;
    int userRoot = bpr ->user;
    int timestampRoot = bpr->timestamp;
    int messageRoot = bpr->message;
    free_bplus_roots(bpr);


    // arrays to keep track of counted users
	bool usersFromNebraska[userCount];
	int userMessageCount[userCount];
	for (int i = 0; i < userCount; i++)
    {
		usersFromNebraska[i] = false;
		userMessageCount[i] = 0;
	}
    
    // get the hash for "Nebraska"
    state_t *fakeState = (state_t *)malloc(sizeof(state_t));
    sprintf(fakeState->name, "Nebraska");
    int stateKey = (int) hash_state(fakeState);
    free_state(fakeState);
    
    // query state b+ tree for nebraska state
    search_result_t *stateSearchResult = search_bplus(stateRoot, TABLE_TYPE_STATE, stateKey);
    
    if (stateSearchResult->count != 1)
    {
        printf("WARNING: We found !1 states matching Nebraska. This is problematic.\n");
    }
    
    // get Nebraska's stateId
    state_t *state = read_state(stateSearchResult->head->fileNumber);
    int nebraskaId = state->stateId;

    // get and mark users from Nebraska as countable
    search_result_t *userSearchResult = search_bplus(userRoot,TABLE_TYPE_USER, nebraskaId);
    search_result_node_t *uSearchNode = userSearchResult->head;
    
    for (; uSearchNode != NULL; uSearchNode = uSearchNode->next)
    {
        user_t *user = read_user(uSearchNode->fileNumber);
        usersFromNebraska[user->userId] = true;
        free_user(user);
    }

    // timestamps are hashed into ints as HHMM
    int startTime = 800;
    int endTime = 900;
    
    // query for timestamps between 8 and 9 (incusive)
    search_result_t *timestampSearchResult = search_bplus_range(timestampRoot, TABLE_TYPE_TIMESTAMP, startTime, endTime);
    if (timestampSearchResult->count != 61)
    {
        printf("WARNING: didn't find 61 separate timestamps. Did something go wrong?\n");
    }
    
    // convert linked list of timestamp file numbers into array of timestamp ids
    int validTimeIds[timestampSearchResult->count];
    search_result_node_t *tsSearchNode = timestampSearchResult->head;
    for (int i = 0; i < timestampSearchResult->count; i ++)
    {
        timestamp_t *timestamp = read_timestamp(tsSearchNode->fileNumber);
        validTimeIds[i] = timestamp->timestampId;
        tsSearchNode = tsSearchNode->next;
        free_timestamp(timestamp);
    }

    // for each timestamp id, query the message tree to get messages with that timestamp id
    int maxUserID = 0;
    int maxMessageCount = 0;
    for (int i = 0; i < timestampSearchResult->count; i ++)
    {
        search_result_t *messageSearchResult = search_bplus(messageRoot, TABLE_TYPE_MESSAGE, validTimeIds[i]);
        search_result_node_t *mSearchNode = messageSearchResult-> head;
        
        // loop over all the matching messages
        for(; mSearchNode != NULL; mSearchNode = mSearchNode->next)
        {
            message_t *message = read_message(mSearchNode->fileNumber);
            if (usersFromNebraska[message->userId])
            {
                userMessageCount[message->userId]++;
                if (userMessageCount[message->userId] > maxMessageCount)
                {
                    maxMessageCount = userMessageCount[message->userId];
                    maxUserID = message->userId;
                }
            }
            free_message(message);
        }
        free_search_result(messageSearchResult);
    }
    
    free_search_result(timestampSearchResult);
    
    printf("Max number of messages is %d, sent by User ID %d\n", maxMessageCount,maxUserID);
    
    // end timing the program
    gettimeofday(&sysTimeEnd, NULL);
    float totalTime = (sysTimeEnd.tv_sec - sysTimeStart.tv_sec)
    + (sysTimeEnd.tv_usec - sysTimeStart.tv_usec) / 1000000.0f;
    printf("Process time %f seconds\n", totalTime);

    return 0;
}
