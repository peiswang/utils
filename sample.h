#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define DIM 5

typedef struct feature_node
{
    double feature[DIM];
    struct list_head list;
} feature_node;

typedef struct sample_node
{
    struct feature_node feature_head;
    struct list_head list;
} sample_node;

struct samples
{
    struct sample_node * sample_head;
    int sample_count;
    int * feature_count_per_sample;
};

struct samples * loadSample( const char* filename )
{
    int i,j;
    int sample_count = 0;
    FILE *pf = fopen( filename, "rt" );
    if(pf==NULL)
    {
        printf("Error open file!\n");
        return 0;
    }

    fscanf(pf,"sample_count= %d\n",&sample_count);
    
    struct samples * p_samples = (struct samples*)malloc(sizeof(struct samples));
    p_samples->sample_count = sample_count;
    p_samples->feature_count_per_sample = (int *)calloc( sample_count, sizeof(int) );

    struct sample_node *sample_head = (struct sample_node *)malloc(sizeof(struct sample_node));
    sample_head->list = LIST_HEAD_INIT(sample_head->list);

    p_samples->sample_head = sample_head;

    int count = 0;
    int sample_index = 0;
    while(sample_index<sample_count)
    {
        fscanf( pf, "# %d\n", &count );
        p_samples->feature_count_per_sample[sample_index++] = count;
        struct sample_node *sample_tmp = (struct sample_node *)malloc(sizeof(sample_node));
        sample_tmp->feature_head.list = LIST_HEAD_INIT(sample_tmp->feature_head.list);
        while(count-->0)
        {
            struct feature_node *feature_tmp = (struct feature_node *)malloc(sizeof(struct feature_node));
            for(i=0;i<DIM;i++)
            {
                fscanf(pf, "%lf", &feature_tmp->feature[i]);
            }
            list_add_tail(&feature_tmp->list, &sample_tmp->feature_head.list);
            fscanf(pf,"\n");
        }
        list_add_tail(&sample_tmp->list, &sample_head->list);
    }
    return p_samples;
}

void printSample(struct samples * p_samples)
{
    int i = 0;
    struct sample_node *sample_head = p_samples->sample_head;

    struct list_head *pos_sample, *pos_feature;
    struct sample_node *p_sample;
    struct feature_node *p_feature;
    printf("sample_count= %d\n", p_samples->sample_count);

    int sample_index = 0;
    list_for_each( pos_sample, &sample_head->list )
    {
        printf("# %d\n", p_samples->feature_count_per_sample[sample_index++]);
        p_sample = list_entry( pos_sample, struct sample_node, list );
        list_for_each( pos_feature, &p_sample->feature_head.list )
        {
            p_feature = list_entry( pos_feature, struct feature_node, list );
            for(i=0;i<DIM;i++)
            {
                printf("%f ", p_feature->feature[i]);
            }
            printf("\n");
        }
    }
}

#endif
