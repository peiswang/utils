#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct obs_vec_list{
    int ot[10];
    struct list_head list;
} obs_vec_list;

typedef struct {
    struct obs_vec_list head;
    struct list_head list;
} obs_seq_list;


int main()
{
    obs_vec_list head = {
        .ot = {0},
        .list = LIST_HEAD_INIT(head.list)
    };
    int i = 0;
    int j = 0, k=0;
    for(i=0;i<5;i++)
    {
        obs_vec_list *tmp = (obs_vec_list*)malloc(sizeof(obs_vec_list));
        for(j=0;j<10;j++)
        {
            tmp->ot[j] = i;
        }
        list_add_tail(&tmp->list,&head.list);
    }
printf("ddd\n");
    struct list_head *pos;
    obs_vec_list *p;
    list_for_each(pos,&head.list)
    {
        p = list_entry(pos,obs_vec_list, list);
        printf("%d\n", p->ot[3]);
    }


    printf("2222\n");
    obs_seq_list seq_head;
    seq_head.list = LIST_HEAD_INIT(seq_head.list);
    int sss = 0;
    for(i=0;i<5;i++)
    {
        obs_seq_list *tmp = (obs_seq_list*)malloc(sizeof(obs_seq_list));
        tmp->head.list = LIST_HEAD_INIT(tmp->head.list);
        for(j=0;j<10;j++)
        {
            obs_vec_list *tmp2 = (obs_vec_list*)malloc(sizeof(obs_vec_list));
            for(k=0;k<10;k++)
            {
                tmp2->ot[k] = i*10+j;//sss++;
            }
            list_add_tail(&tmp2->list,&tmp->head.list);

        }
        list_add_tail(&tmp->list, &seq_head.list);

    }

    struct list_head *posseq;
    struct list_head *posvec;
    obs_seq_list *pseq;
    obs_vec_list *pvec;
    list_for_each(posseq,&seq_head.list)
    {
        pseq = list_entry(posseq,obs_seq_list, list);
        list_for_each(posvec,&pseq->head.list)
        {
            pvec = list_entry(posvec,obs_vec_list, list);
            printf("%d\t", pvec->ot[3]);
        }
        printf("\n");
    }
    printf("end\n");
    return 0;
}
