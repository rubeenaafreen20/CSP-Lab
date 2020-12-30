#include <stdio.h>
#include <stdlib.h>
#include "common_functions_1.h"


int main()
{
    float x_n[]={0.5377, 1.8339, -2.2588, 0.8622, 0.3188,-1.3077, -0.4336, 0.3426, 3.5784,
     2.7694,-1.3499,3.0349, 0.7254, -0.0631, 0.7147, -0.2050, -0.1241, 1.4897, 1.4090,1.4172};
    float h_n[]={0.6715, -1.2075, 0.7172, 1.6302, 0.4889, 1.0347, 0.7269,
     -0.3034, 0.2939, -0.7873, 0.8884, -1.1471, -1.0689, -0.8095, -2.9443};


    size_t x_len = sizeof (x_n)/sizeof(float);              /**< Length of x[n]=L */
    size_t h_len = sizeof (h_n)/sizeof(float);              /**< length of h[n]=M */
    int y_len = x_len+h_len-1;                              /**< Length of output y[n]=L+M-1 */


                       /**< CONVOLUTION */

    int i=0;
    float *y_n= convolution(x_n,h_n,x_len,h_len,y_len);
    printf("convolution sum y[n]= [");
    for(i=0;i<y_len;i++)
        {
            printf("%.4f",y_n[i]);
            if (i<y_len-1)
            {
                printf(", ");
            }
        }
        printf("]");
    free(y_n);

                                                /**< CORRELATION */


  float* corr_n= correlation(x_n,h_n,x_len,h_len,y_len);
    int j;
    printf("\n\n Correlation output Rxh[n]= [");
    for(j=0;j<y_len;j++)
        {
            printf("%.4f",corr_n[j]);
            if (j<y_len-1)
            {
                printf(", ");
            }
        }
        printf("]");
    free(corr_n);

                                        /**< DOWN SAMPLING */

float x_d[]={0.3252, -0.7549, 1.3703, -1.7115, -0.1022, -0.2414, 0.3192,
0.3129, -0.8649, -0.0301, -0.1649,0.6277, 1.0933, 1.1093, -0.8637, 0.0774,
 -1.2141, -1.1135, -0.0068, 1.5326, -0.7697, 0.3714, -0.2256, 1.1174, -1.0891,
 0.0326, 0.5525, 1.1006, 1.5442, 0.0859, -1.4916, -0.7423, -1.0616, 2.3505, -0.6156, 0.7481};

    size_t length_x=sizeof (x_d)/sizeof(float);
    int m=2;                /**< downsampling factor */
    float* down_sampled= downsampling(x_d,m,length_x);
    printf("\n\n Downsampled output y[n]= x[Mn]= [");
    for(j=0;j<length_x/m;j++)
        {
            printf("%.4f",down_sampled[j]);
            if (j<length_x/m-1)
            {
                printf(", ");
            }
        }
        printf("]");
    free(down_sampled);

                                            /**< UP SAMPLING */

float x_u[] = {0.3252, 1.3703, -0.1022, 0.3192, -0.8649, -0.1649, 1.0933, -0.8637,
 -1.2141, -0.0068, -0.7697, -0.2256, -1.0891, 0.5525, 1.5442, -1.4916, -1.0616, -0.6156};
    size_t length_xu=sizeof (x_u)/sizeof(float);
    int l=2;                                                      /**< Up sampling factor */
    float* up_sampled= upsampling(x_u,l,length_xu);
    printf("\n\n Up sampled output y[n]=x[n/L]= [");
    for(j=0;j<length_xu*l;j++)
        {
            printf("%.4f",up_sampled[j]);
            if (j<length_xu*l-1)
            {
                printf(", ");
            }
        }
        printf("]");
    free(up_sampled);

return 0;
}




