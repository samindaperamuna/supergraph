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
        queryHelper->users = (user*) post_loader(&queryHelper->n_users, _helper->file_name);
    } else {
        queryHelper->posts = (post*) post_loader(&queryHelper->n_posts, _helper->file_name);
    }
}

result* find_all_reposts(post* posts, size_t count, uint64_t post_id, query_helper* helper) {
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