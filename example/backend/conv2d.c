#include "backend.h"

void conv2D(const float *input,                                                // input image
            const uint16_t dim_im_in_x,                                        // input image dimention x
            const uint16_t dim_im_in_y,                                        // input image dimention y
            const uint16_t ch_im_in,                                           // number of input image channels
            const float *weight,                                               // kernel weights
            const uint16_t ch_im_out,                                          // number of filters, i.e., output image channels
            const uint16_t dim_kernel_x,                                       // filter kernel size x
            const uint16_t dim_kernel_y,                                       // filter kernel size y
            const uint16_t padding_x,                                          // padding sizes x
            const uint16_t padding_y,                                          // padding sizes y
            const uint16_t stride_x,                                           // stride x
            const uint16_t stride_y,                                           // stride y
            const float *bias,                                                 // bias
            float *output,                                                     // output image
            const uint16_t dim_im_out_x,                                       // output image dimension x
            const uint16_t dim_im_out_y                                        // output image dimension y
)
{
    int i, j, k, l, m, n;
    float conv_out = 0.0f;
    int in_row, in_col;

    // For each filter
    for (i = 0; i < ch_im_out; i++)
    {
        // For each image dimension
        for (j = 0; j < dim_im_out_y; j++)
        {
            for (k = 0; k < dim_im_out_x; k++)
            {
                conv_out = bias[i];
                // For each kernel dimension
                for (m = 0; m < dim_kernel_y; m++)
                {
                    for (n = 0; n < dim_kernel_x; n++)
                    {
                        // if-for implementation
                        in_row = stride_y * j + m - padding_y;
                        in_col = stride_x * k + n - padding_x;
                        if (in_row >= 0 && in_col >= 0 && in_row < dim_im_in_y && in_col < dim_im_in_x)
                        {
                            // For each input channel
                            for (l = 0; l < ch_im_in; l++)
                            {
                                conv_out += input[(in_row * dim_im_in_x + in_col) * ch_im_in + l] *
                                            weight[i * ch_im_in * dim_kernel_y * dim_kernel_x + (m * dim_kernel_x + n) * ch_im_in +
                                               l];
                            }
                        }
                    }
                }
                output[i + (j * dim_im_out_x + k) * ch_im_out] = conv_out;
            }
        }
    }
}