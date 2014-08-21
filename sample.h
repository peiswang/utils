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

struct sample_node * loadSample( const char* filename,int sample_count )
{
    int i,j;
    FILE *pf = fopen( filename, "rt" );
    if(pf==NULL)
    {
        printf("Error open file!\n");
        return 0;
    }
    struct sample_node *sample_head = (struct sample_node *)malloc(sizeof(struct sample_node));
    sample_head->list = LIST_HEAD_INIT(sample_head->list);
    int count = 0;
    while(sample_count-->0)
    {
        fscanf( pf, "# %d\n", &count );
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
    return sample_head;
}

void printSample(struct sample_node * sample_head)
{
    int i = 0;
    struct list_head *pos_sample, *pos_feature;
    struct sample_node *p_sample;
    struct feature_node *p_feature;
    list_for_each( pos_sample, &sample_head->list )
    {
        printf("#\n");
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
