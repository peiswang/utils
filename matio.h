
#ifndef _MAT_I_O_H_
#define _MAT_I_O_H_

#include <stdio.h>
#include <assert.h>
#include "cv.h"

int loadmat( const char* filename, int var_count, CvMat** data )
{
    const int M = 125000;
    FILE* f = fopen( filename, "rt" );
    CvMemStorage* storage;
    CvSeq* seq;
    char buf[M];
    float* el_ptr;
    CvSeqReader reader;
    int i, j;

    if( !f )
    {
        printf("Cannot open file!\n");
        return 0;
    }

    el_ptr = new float[var_count];
    storage = cvCreateMemStorage();
    seq = cvCreateSeq( 0, sizeof(*seq), (var_count)*sizeof(float), storage );

    printf("loading mat...\n");
    while(1)
    {
        char* ptr;
        if( !fgets( buf, M, f ) )
            break;
        if( buf[0] == '\n' ) 
            continue;
        ptr = buf;
        for( i = 0; i < var_count; i++ )
        {
            int n = 0;
            sscanf( ptr, "%f%n", el_ptr + i, &n );
            ptr += n;
        }
        if( i < var_count )
            break;
        cvSeqPush( seq, el_ptr );
    }
    fclose(f);


    *data = cvCreateMat( seq->total, var_count, CV_32F );

    cvStartReadSeq( seq, &reader );

    for( i = 0; i < seq->total; i++ )
    {
        const float* sdata = (float*)reader.ptr;
        float* ddata = data[0]->data.fl + var_count*i;

        for( j = 0; j < var_count; j++ )
            ddata[j] = sdata[j];
        CV_NEXT_SEQ_ELEM( seq->elem_size, reader );
    }

    printf("Mat loaded:\n\trows: %d\n\tcols: %d\n", seq->total, var_count);
    cvReleaseMemStorage( &storage );
    delete el_ptr;
    return 1;
}

int printmat(CvMat *_mat)
{
    cv::Mat mat = cv::cvarrToMat(_mat);
    assert( mat.type() == CV_32F || mat.type() == CV_32S );
    int i,j;
    void* sample;
    for(i=0;i<mat.rows;i++)
    {
        switch(mat.type())
        {
            case CV_32F:
                sample = mat.ptr<float>(i);
                for(j=0;j<mat.cols;j++)
                {
                    printf("%f ", ((float*)sample)[j]);
                }
                break;
            case CV_32S:
                sample = mat.ptr<int>(i);
                for(j=0;j<mat.cols;j++)
                {
                    printf("%d ", ((int*)sample)[j]);
                }
                break;
        }
        printf("\n");
    }
    return 1;
}

int savemat(const char *filename, CvMat *_mat)
{
    cv::Mat mat = cv::cvarrToMat(_mat);
    assert( mat.type() == CV_32F || mat.type() == CV_32S );
    FILE *f = fopen( filename, "w" );
    if(!f)
    {
        printf("Cannot create file %s\n!", filename);
        return 0;
    }
    int i,j;
    void* sample;
    for(i=0;i<mat.rows;i++)
    {
        switch(mat.type())
        {
            case CV_32F:
                sample = mat.ptr<float>(i);
                for(j=0;j<mat.cols;j++)
                {
                    fprintf( f, "%f ", ((float*)sample)[j] );
                }
                break;
            case CV_32S:
                sample = mat.ptr<int>(i);
                for(j=0;j<mat.cols;j++)
                {
                    fprintf( f, "%d ", ((int*)sample)[j] );
                }
                break;
        }
        fprintf( f, "\n" );
    }
    return 1;
}

#endif
