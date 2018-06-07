#include <pthread.h>
#include <stdio.h>
#include "supergraph.h"
#include "supergraph_loader.h"

#define NUM_THREAD 2
#define USERS_FILE "social.users"
#define POSTS_FILE "social.posts"

static size_t n_proc = 0;

query_helper* engine_setup(size_t n_processes) {
    n_proc = n_processes;

    // Allocate memory for query helper.
    query_helper* helper = malloc(sizeof (query_helper));

    pthread_t threads[NUM_THREAD];

    load_helper user_load_helper;
    user_load_helper.isUser = 1;
    user_load_helper.file_name = USERS_FILE;
    user_load_helper.query_helper = helper;

    load_helper post_load_helper;
    post_load_helper.isUser = 0;
    post_load_helper.file_name = POSTS_FILE;
    post_load_helper.query_helper = helper;

    for (int i = 0; i < NUM_THREAD; i++) {
        if (i == 0)
            pthread_create(threads + i, NULL, threadLoader, (void*) &user_load_helper);
        else
            pthread_create(threads + i, NULL, threadLoader, (void*) &post_load_helper);
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    return helper;
}

void* threadLoader(void* helper) {
    load_helper* _helper = (load_helper*) helper;
    char* file_name = _helper->file_name;
    query_helper* queryHelper = _helper->query_helper;

    if (_helper->isUser) {
        queryHelper->users = (user*) post_loader(&queryHelper->n_users, file_name);
    } else {
        queryHelper->posts = (post*) post_loader(&queryHelper->n_posts, file_name);
    }
}

result* find_all_reposts(post* posts, size_t count, uint64_t post_id, query_helper* helper) {
    // TODO: Clean up memory.
    post *reposts;
    Queue *queue = constructQueue(count);
    post* post = NULL;
    int repostCount = 0;

    // Allocate and initialise the array holding the visited status of the post.
    bool *visited = (bool*) malloc(sizeof (bool) * count);
    for (int i = 0; i < count; i++) {
        visited[i] = false;
    }

    // FInd the initial post.
    // Check for unvisited nodes and apply BFS.
    for (int i = 0; i < count; i++) {
        if (!visited[i] && post == NULL) {
            post = bfsSearch(i, visited, queue, posts, post_id);
        }
    }

    reposts = post;
    repostCount++;

    if (post != NULL) {
        // Clear the queue.
        destructQueue(queue);
        queue = constructQueue(count);

        // Clear booleans.
        visited = (bool*) realloc(visited, sizeof (bool) * count);
        for (int i = 0; i < count; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < post->n_reposted; i++) {
            Node *node = (Node*) malloc(sizeof (Node));
            node->prev = NULL;
            node->data = post->reposted_idxs[i];
            enqueue(queue, node);
        }

        // Count and collect all the reposts.
        bfsCollect(visited, queue, posts, reposts, &repostCount);

        // Append to result structure.
        result* res = (result*) malloc(sizeof (result));
        res->elements = (void*) reposts;
        res->n_elements = repostCount;

        return res;
    }

    return NULL;
}

void bfsCollect(bool* visited, Queue* queue, post* posts, post* reposts, int* count) {
    Node *node = (Node*) malloc(sizeof (Node));
    node->prev = NULL;
    node->data = 0;

    enqueue(queue, node);

    while (!isEmpty(queue)) {
        node = dequeue(queue);
        int index = node->data;

        if (visited[index] == false) {
            visited[index] = true;
            (*count)++;
            *(++reposts) = posts[index];
            for (int i = 0; i < posts[index].n_reposted; i++) {
                Node *temp = (Node*) malloc(sizeof (Node));
                temp->prev = NULL;
                temp->data = posts[index].reposted_idxs[i];
                enqueue(queue, temp);
            }
        }
    }
}

post *bfsSearch(int start, bool* visited, Queue* queue, post* posts, uint64_t post_id) {
    Node *node = (Node*) malloc(sizeof (Node));
    node->prev = NULL;
    node->data = start;

    enqueue(queue, node);

    while (!isEmpty(queue)) {
        node = dequeue(queue);
        int index = node->data;

        if (visited[index] == false) {
            visited[index] = true;
            if (posts[index].pst_id == post_id) {
                post *temp = &posts[index];
                return temp;
            }
            for (int i = 0; i < posts[index].n_reposted; i++) {
                Node *temp = (Node*) malloc(sizeof (Node));
                temp->prev = NULL;
                temp->data = posts[index].reposted_idxs[i];
                enqueue(queue, temp);
            }
        }
    }

    return NULL;
}

result* find_original(post* posts, size_t count, uint64_t post_id, query_helper* helper) {
    return NULL;
}

result* shortest_user_link(user* users, size_t count, uint64_t userA, uint64_t userB, query_helper* helper) {
    return NULL;
}

result* find_bots(user* users, size_t user_count, post* posts, size_t post_count, criteria* crit, query_helper* helper) {
    return NULL;
}

void engine_cleanup(query_helper* helper) {
    free(helper->posts);
    free(helper->users);
    free(helper);
}