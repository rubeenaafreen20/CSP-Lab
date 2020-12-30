#include <stdio.h>
#include <stdlib.h>
#include "common_functions.h"
#include "math.h"


int main()
{
    float h_n[]={-0.0013,0.0000, 0.0020, -0.0000, -0.0038, 0.0000, 0.0071, -0.0000, -0.0124, 0.0000, 0.0204,
     -0.0000, -0.0330, 0.0000, 0.0542, -0.0000, -0.1002, 0.0000, 0.3163, 0.5000, 0.3163, 0.0000, -0.1002,-0.0000,
      0.0542, 0.0000, -0.0330, -0.0000, 0.0204, 0.0000, -0.0124, -0.0000, 0.0071, 0.0000, -0.0038, -0.0000, 0.0020, 0.0000,-0.0013};
        /**< Generate x[n] from equation given */
    int f0=100,f1=200,f2=300,fs=1600,n=0;
    int x_len=48;
    float x_n[x_len];
    printf("\ninput signal generated from equation:\nx[n]= [");
    for(n=0;n<x_len;n++)
    {
        x_n[n]=1*sin((2*M_PI*f0*n)/fs)+ 0.5*sin((2*M_PI*f1*n)/fs) + 0.6*sin((2*M_PI*f2*n)/fs);
        printf("%.4f",x_n[n]);
        if(n<x_len-1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    //size_t x_len = sizeof (x_n)/sizeof(float);              /**< Length of x[n]=L */
    size_t h_len = sizeof (h_n)/sizeof(float);              /**< length of h[n]=M */

                       /**< LPF with gain 1*/
    int xf_len,i;
    float *xf_n = convolution(h_n,x_n,h_len,x_len,&xf_len);
    printf("\nOutput of first Low Pass Filter: \nxf[n] = [");
    for(i=0; i<xf_len; i++)
    {
        printf("%.4f",xf_n[i]);
        if(i<xf_len-1)
        {
            printf(", ");
        }
    }
    printf("]\n ");
                              /**< Discarding first and last (lh-1)/2 samples*/
    int xff_len,j;
    xff_len=xf_len-(h_len-1);
    float xff_n[xff_len];
    printf("\n Signal xf[n] with first and last (h_len-1)/2 samples discarded:\nxff_n[n] = [");
    for (j = 0; j < xff_len; j++)
    {
        xff_n[j] = xf_n[j +((h_len-1)/2)];
        printf("%.4f", xff_n[j]);
        if(j<xff_len-1)
        {
            printf(", ");
        }
    }
    printf("]\n");

                    /**< Apply output from LPF(xf_n) to decimator */

   int m=2,k=0;                                                  /**< downsampling factor */
    float *xd_n= downsampling(xff_n,m,xff_len);
    printf("\nDownsampled output:\nxd_n[n]= xff_n[Mn]= [");
    for(k=0;k<xff_len/m;k++)
        {
            printf("%.4f",xd_n[k]);
            if (k<xff_len/m-1)
            {
                printf(", ");
            }
        }
        printf("]\n");

        free(xf_n);

                                            /**< UP SAMPLING */

    int xd_len=0;
    if (xff_len%2==0)
    {
        xd_len=(xff_len/2);
    }
    else
    {
        xd_len=(xff_len/2)+1;
    }
    int l=2, xu_len=1,p=0;                                                      /**< Up sampling factor */
    float* xu_n= upsampling(xd_n,l,xd_len);
    printf("\nUp sampled output:\nxu[n]=xd[n/L]= [");
    for(p=0;p<xd_len*l;p++)
        {
            printf("%.4f",xu_n[p]);
            xu_len=p+1;
            if (p<xd_len*l-1)
            {
                printf(", ");
            }
        }
        printf("]\n");

    free(xd_n);
                                    /**< Anti Imaging Filter with gain L=2*/

    int q,r;
    float h1_n[h_len];
    printf("\nImpulse response of LPF with gain L:\nh1[n]= [");

    for(q=0; q<h_len;q++)
    {
        h1_n[q]=2*h_n[q];
        printf("%.4f",h1_n[q]);
        if(q<h_len-1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    int h1_len=h_len;
    int yf_len;
    float *yf_n=convolution(h1_n,xu_n,h1_len,xu_len,&yf_len);
    printf("\n output from LPF with gain L=\ny_f[n]=[");
    for(r=0; r<yf_len; r++)
        {
            printf("%.4f",yf_n[r]);
            if (r <yf_len-1)
            {
                printf(", ");
            }
        }
    printf("]\n");
    free(xu_n);
                            /**< Discarding first and last (lh-1)/2 samples from yf_n*/
    int s;
    int y_len = (yf_len-(h1_len-1));
    float y_n[y_len];
    printf("\n Signal yf[n] with first and last (h1_len-1)/2 samples discarded:\ny[n]=[");
    for (s = 0; s<y_len; s++)
    {
        y_n[s] = yf_n[s +((h1_len-1)/2)];
        printf("%0.4f", y_n[s]);
        if(s<y_len-1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    free(yf_n);

            /**< ERROR VECTOR */
    int t=0;
    float e_n[y_len];
    printf("\nError vector between x[n] and y[n]:\ne[n]= [");
    for(t=0;t<y_len;t++)
    {
        e_n[t]=y_n[t]-x_n[t];
        printf("%.4f",e_n[t]);
        if(t<y_len-1)
        {
            printf(", ");
        }
    }
    printf("]");

            /**< Average error */
float sum=0;
 for(i=0; i<y_len; i++)
    {
        sum = sum + fabs(e_n[i]);
    }
printf("\nAverage error is = %.4f", sum/y_len);
return 0;
}




