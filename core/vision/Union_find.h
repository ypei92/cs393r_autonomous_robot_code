#ifndef MERGING_BLOB_H_INCLUDED
#define MERGING_BLOB_H_INCLUDED
#include <iostream>
#include <vector>

class MergeBlob
{
	private:

		int Root(int i);
		int Count_Sons(int i);
		bool If_Connected( int i , int j);
		void Union(int i , int j);
		void Union_process();
		void Calculate_blob();

		unsigned char *array_image;
		int *array_tree;
		int *array_weight;
		int image_length;
		int image_height;
		int valid_length_total;
		int neglect_factor_x;
		int neglect_factor_y;
		int blob_number;
		int blob_pixel_number_threshold;

/*
		struct Boundingbox
		{
			int vertex_x;
			int vertex_y;

			int length;
			int height;

			Boundingbox(int boundingbox_vertex_x = 0 , int boundingbox_vertex_y = 0 ,
				   		int boundingbox_length = 0 , int boundingbox_height = 0)
			{
				vertex_x = boundingbox_vertex_x;
				vertex_y = boundingbox_vertex_y;
				length = boundingbox_length;
				height = boundingbox_height;
			}
		};
*/

	public:

		struct Blob
		{
			int centroid_x;
			int centroid_y;
			int color;
			int boundingbox_length; //x
			int boundingbox_height; //y
			int boundingbox_vertex_x;
			int boundingbox_vertex_y;

			int *pixel_index_x;
			int *pixel_index_y;

			std::vector<Blob*> blobs_connected_to_top;
			std::vector<Blob*> blobs_connected_to_bottom;
			bool beacon_candidate;

			Blob()
			{
				centroid_x = -1;
				centroid_y = -1;
				color = -1;
				boundingbox_vertex_x = -1;
				boundingbox_vertex_y = -1;
				boundingbox_height = -1;
				boundingbox_length = -1;

				pixel_index_x = NULL;
				pixel_index_y = NULL;
				
				beacon_candidate = true;
			}
			~Blob()
			{
			    //if( pixel_index_x != NULL ) printf("x not null\n");
			    //if( pixel_index_y != NULL ) printf("y not null\n");

			    delete []pixel_index_x;
			    delete []pixel_index_y;
            }
		};

		Blob *blob;

		MergeBlob(unsigned char *image, int x , int y , int neg_factor_x , int neg_factor_y , int pixel_threshold)
		{
			int i , j , k = 0;

			image_length = x;
			image_height = y;
			neglect_factor_x = neg_factor_x;
			neglect_factor_y = neg_factor_y;
			blob_pixel_number_threshold = pixel_threshold;

			valid_length_total =  x*y/(neg_factor_x * neg_factor_y );

			array_image = new unsigned char[valid_length_total];
			array_tree = new int[valid_length_total];
			array_weight = new int[valid_length_total];

			for( i = 0 ; i < y ; i = i + neg_factor_y)
			{
				for ( j = 0 ; j < x ; j = j + neg_factor_x)
				{
					array_image[k] = image[i*x + j];
					array_tree[k] = k;
					array_weight[k] = 1;
					++k;
				}
			}

			blob_number = 0;
			blob = NULL;

			Union_process();
			Calculate_blob();
		}
		~MergeBlob()
		{
			delete []array_tree;
			delete []array_weight;
			delete []array_image;
			delete []blob;
		}

        void DisplayBlob(int i);
        void Display_array_image();
        void Display_array_tree();
        void Display_array_weight();
		int get_blob_number(){return blob_number;}
};

#endif // MERGING_BLOB_H_INCLUDED
