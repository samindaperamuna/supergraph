#ifndef SUPERGRAPH_H
#define SUPERGRAPH_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "queue.h"

typedef struct query_helper query_helper;
typedef struct result result;
typedef struct criteria criteria;
typedef struct user user;
typedef struct post post;
typedef struct load_helper load_helper;

struct query_helper {
    int dummy_field;
    post* posts;
    size_t n_posts;
    user* users;
    size_t n_users;
};

struct result {
    void* elements;
    size_t n_elements;
};

struct criteria {
    float oc_threshold;
    float acc_rep_threshold;
    float bot_net_threshold;
};

struct user {
    uint64_t user_id;
    size_t* follower_idxs;
    size_t n_followers;
    size_t* following_idxs;
    size_t n_following;
    size_t* post_idxs;
    size_t n_posts;
};

struct post {
    uint64_t pst_id;
    uint64_t timestamp;
    size_t* reposted_idxs;
    size_t n_reposted;
};

struct load_helper {
    char isUser;
    char* file_name;
    query_helper* query_helper;
};

query_helper* engine_setup(size_t n_processes);

void* threadLoader(void* helper);

post *bfsSearch(int start, bool* visited, Queue* queue, post* posts, uint64_t post_id);

void bfsCollect(bool* visited, Queue* queue, post* posts, post* reposts, int *count);

result* find_all_reposts(post* posts, size_t count, uint64_t post_id, query_helper* helper);

result* find_original(post* posts, size_t count, uint64_t post_id, query_helper* helper);

result* shortest_user_link(user* users, size_t count, uint64_t userA, uint64_t userB, query_helper* helper);

result* find_bots(user* users, size_t user_count, post* posts, size_t post_count, criteria* crit, query_helper* helper);

void engine_cleanup(query_helper* helper);

#endif