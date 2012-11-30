#include "TerrainTile.h"
#include "SimplexNoise.h"
#include "geo/Mesh.h"
#include "Image2D.h"

namespace revel
{
	TerrainTile::TerrainTile(std::shared_ptr<renderer::RenderContext> ctx, float x, float y, int res, float len, float hei)
	{
		auto mesh = std::make_shared<geo::Mesh>();    
	    auto meshp = mesh->create_vertex_attrib<point3>("position");
	    auto meshn = mesh->create_vertex_attrib<vec3>("normals");
	    auto mesht = mesh->create_vertex_attrib<vec2>("uv0");
	    

	    auto meshi = mesh->indices<u32>();
		
		//Image2D<pixel::Gray_f32> hmap(res, res);


		f32 d = (f32)len/(f32)res;
		for(int i=0; i<res ; i++)
		{
			for(int j=0 ; j<res ; j++)
			{
				//std::cout<<SimplexNoise::noise(x+j*d,y+i*d)<<" ";
				//vec3_f32 vert(x+j*d, y+i*d, SimplexNoise::noise(x+j*d,y+i*d)); 

				//tilep->data().push_back(vert);
				//f32 h = SimplexNoise::noise(x+j*d,y+i*d)*hei;
				//hmap(j, i).val = h;
				meshp->data().push_back(point3(j,i,SimplexNoise::noise(x+j*d,y+i*d)*hei));
				mesht->data().push_back(vec2(j / (128.0f / 16), i / (128.0f / 16)));
			}
			//std::cout<<"\n";
		}

		for(int i = 0 ; i < res -1 ; i++)
		{
			for(int j = 0 ; j < res -1 ; j++)
			{
				meshi->add_triangle(i*res+j+res, i*res+j+res+1, i*res+j+1);
	    		meshi->add_triangle(i*res+j+1, i*res+j, i*res+j+res);
			}		
		}


		std::vector<vec3> normals;
		normals.reserve(128*128);
/*
		


		for (i32 y = 1; y < res - 1; ++y)
		{
			for (i32 x = 1; x < res - 1; ++x)
			{
				//upper left

				vec3 u = point3(x, y+1, hmap(x, y+1).val) - point3(x, y, hmap(x, y).val);
				vec3 l = point3(x-1, y, hmap(x-1, y).val) - point3(x, y, hmap(x, y).val);
				vec3 r = point3(x+1, y, hmap(x+1, y).val) - point3(x, y, hmap(x, y).val);
				vec3 d = point3(x, y-1, hmap(x, y-1).val) - point3(x, y, hmap(x, y).val);

				vec3 uln = math::cross(u, l);
				vec3 urn = math::cross(r, u);
				vec3 lrn = math::cross(d, r);
				vec3 lln = math::cross(l, d);

				math::normalize(uln);
				math::normalize(urn);
				math::normalize(lrn);
				math::normalize(lln);

				normals[y * res + x] = (uln + urn + lrn + lln)/4;
			}
		}

		meshn->data() = normals;
*/

		

		for (u32 i = 0; i < res - 1; ++i)
		{
			for (u32 j = 0; j < res - 1; ++j)
			{
				u32 i1 = (i * res) + j;
				u32 i2 = (i * res) + j+1;
				u32 i3 = ((i+1) * res) + j;

				point3 p1 = meshp->data()[i1];
				point3 p2 = meshp->data()[i2];
				point3 p3 = meshp->data()[i3];

				vec3 v1 = p2 - p1;
				vec3 v2 = p1 - p3;

				u32 index = (i * (res-1)) + j;

				normals.push_back(-math::cross(v1, v2));
			}
		}

		R_LOG_INFO("NORMALS SIZE: " << normals.size());

		for (i32 i = 0; i < res; ++i)
		{
			for (i32 j = 0; j < res; ++j)
			{
				vec3 sum;

				u32 count = 0;

				//bottom left
				if (((j-1) >= 0) && ((i-1)) >= 0)
				{
					//R_LOG_INFO("INDEX: " << ((i-1)*(res-1)) + (j-1));
					sum = sum + normals[((i-1)*(res-1)) + (j-1)];
					count++;
				}

				if ((j < (res-1)) && ((i-1) >= 0))
				{
					sum += normals[((i-1) * (res - 1)) + j];
					count++;
				}

				if (((j-1) >= 0) && (i < (res -1)))
				{
					sum += normals[(i * (res - 1)) + (j-1)];
					count++;
				}

				if ((j < (res-1)) && (i < (res - 1)))
				{
					sum += normals[(i * (res - 1)) + j];
					count++;
				}
				

				sum = sum / (f32)count;

				u32 length = sum.length();

				meshn->data().push_back(-sum / length);
			}
		}

/*
		R_LOG_INFO("Mesh Normals: " << meshn->data().size());

		for (u32 i = 128 + ; i < 128 + 10; ++i)
		{
			R_LOG_INFO("Vertex normal: " << meshn->data()[i].x << ", " << meshn->data()[i].y << ", " << meshn->data()[i].z);
		}

		for (u32 i = 128 + ; i < 128 + 10; ++i)
		{
			R_LOG_INFO("Vertex normal: " << normals()[i].x << ", " << normals()[i].y << ", " << normals()[i].z);
		}
	*/


/*
		for (u32 i = 0; i < meshi->data().size(); i = i+3)
		{
			u32 ind1, ind2, ind3;

			ind1 = meshi->data()[i];
			ind2 = meshi->data()[i+1];
			ind3 = meshi->data()[i+2];

			vec3 v1 = meshp->data()[ind1] - meshp->data()[ind2];
			vec3 v2 = meshp->data()[ind3] - meshp->data()[ind2];

			vec3 normal = math::cross(v1, v2);

			normals.push_back(normal);
		}
*/


		va = ctx->create_vertex_array(mesh);
	}

	TerrainTile::~TerrainTile()
	{

	}
}