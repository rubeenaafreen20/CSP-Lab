#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#include "common_functions_1.h"

                                    /**< convolution */

 float *convolution( float x_n[],float h_n[],size_t x_len,size_t h_len,int *y_len)
        {
            int counter=y_len;                                               /**< length of convolved output  */
           static int k,n,h_start,x_end,x_start=0;
            float *y = (float*) calloc(counter, sizeof(float));             /**< Allocating memory for output */

            for (n=0;n<counter;n++)
            {
            /** We need to start and end points of x[n] & h[n],
             *  because index value more than length of h[n] and x[n] will give stray values.
             * \param n is counter which counts from 0 to length of output y[n].
             */

            x_end = MIN(n,x_len);

              if(n<h_len)
               {
                   h_start=n;
                   x_start=0;
               }
               else
               {
                   h_start=h_len-1;
                   x_start=n-h_len+1;
               }

               for(k=x_start; k<=x_end; k++)
                {
                    y[n] += (x_n[k]) * (h_n[h_start--]);
                }
            }
            return y;
        }

                                    /**< Correlation */


 float *correlation( float x_n[],float h_n[],size_t x_len,size_t h_len,int *y_len)
        {
            static int n,t,k,end,x_end,x_start,h_start,h_end=0;
            float temp;

        int corr_counter=y_len;
        float *rxh = (float*) calloc(corr_counter, sizeof(float));             /**< Allocating memory for output */

          for (k=0;k<corr_counter;k++)
            {
            /** Set the value of h_start, x_start, h_end, x_end */
             t=h_len-1-k;
              if(t>0)
               {
                   h_end=t;
               }
               else
               {
                   h_end=0;
               }

              // h_end=MAXIMUM((h_len-k-1),0);
               if(k<x_len)
               {
                   h_start=h_len-1;
                   x_start=k;
                }
               else
               {
                   h_start=corr_counter-k-1;
                   x_start=x_len-1;
               }

               for(n=h_start;n>=h_end; n--)
                {
                    rxh[k] += (h_n[n]) * (x_n[x_start--]);

                }
            }
        return rxh;
        }


                        /**< DOWN SAMPLING */

        float *downsampling( float x[],int m,size_t length_x)
        {
            int downsamp_counter=length_x;
            float *x_downsampled = (float*) calloc(downsamp_counter, sizeof(float));
            static int w=0;
            for (w=0;m*w<length_x;w++)
                {
                    x_downsampled[w]=x[m*w];
                }

             return x_downsampled;
        }

                    /**< UP SAMPLING */

        float *upsampling( float x[],int l,size_t length_xu)
        {
            int upsamp_counter=length_xu*l;
            float *x_upsampled = (float*) calloc(upsamp_counter, sizeof(float));
            static int w=0;
            for (w=0;w<upsamp_counter;w++)
                {
                    if (w%l==0)
                    {
                        x_upsampled[w]=x[w/l];
                    }
                    else
                    {
                      x_upsampled[w]=0;
                    }
                }

             return x_upsampled;
        }
