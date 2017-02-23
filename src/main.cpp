#include "Ray.hpp"
#include "Vec3.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Ellipsoid.hpp"
#include "Color.hpp"
#include "MtlColor.hpp"
#include "Light.hpp"
#include "Scene.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

enum string_code { // enum structure for turning keywords into tokens
	eEye,
	eViewdir,
	eUpdir,
	eFovv,
	eImsize,
	eBkgcolor,
	eMtlcolor,
	eSphere,
	eEllipsoid,
	eLight,
	eVertex,
	eFace,
	eVertexNormal,
	eTexture,
	eTextureCoordinate,
	eParallel,
	eUnknown
};

void error(string message); // output an error message and exit program
float* getParams(ifstream& in, int n); // grab the next 'n' parameters from the file stream
string_code convertToEnum(string str); // convert a string to one of a set of known keyword tokens
void TraceRay(Ray& ray, Scene& scene, RayPayload& payload);
Color ShadeRay(Ray& ray, Scene& scene, RayPayload& payload,int depth,bool outside);

int main( int argc, char **argv ){
	// create and initialize variables
	ifstream input_params;
	ofstream output_ppm;
	string keyword_check;
	int image_width = -1, image_height = -1;
	bool found_keyword = false;
	int file_name_length = 0;
	Vec3 eye;
	Vec3 viewdir;
	Vec3 updir;
	Vec3 ul,ur,ll,lr;
	float fovv;
	int imsize[2];
	Scene scene;
	Color** output_image;
	float* param_holder;
	float* temp;
	float distance = 5;
	bool texture = false;
	bool parallel = false;


	// Make sure the user specified an input file. If not, tell them how to do so.
	if( argc < 2 ){
		error("you must specify an input file, e.g. \"./raytracer ../examplefile.txt\"");
	}

	// find the length of the file name
	while(argv[1][file_name_length] != '\0'){
		file_name_length++;
	}

	// make sure file is a .txt file
	if(argv[1][file_name_length - 4] != '.' || argv[1][file_name_length - 3] != 't' || argv[1][file_name_length - 2] != 'x' || argv[1][file_name_length - 1] != 't'){
		error("expected a file with the extension '.txt'");
	}

	// open input file and check for failure
	input_params.open(argv[1]);
	if(input_params.fail()){
		error("input file could not be opened");
	}

	// parse input file and get variables
	while(true){
		input_params >> keyword_check;
		// check to see if we've reached the end of the input file
		if(input_params.eof()){
			break;
		}
		switch(convertToEnum(keyword_check)){
			case eEye:
				param_holder = getParams(input_params,3);
				eye.set(param_holder[0],param_holder[1],param_holder[2]);
				scene.m_eye = Vec3(eye);
				delete [] param_holder;
				break;
			case eViewdir:
				param_holder = getParams(input_params,3);
				viewdir.set(param_holder[0],param_holder[1],param_holder[2]);
				viewdir.normalize();
				delete [] param_holder;
				break;
			case eUpdir:
				param_holder = getParams(input_params,3);
				updir.set(param_holder[0],param_holder[1],param_holder[2]);
				updir.normalize();
				delete [] param_holder;
				break;
			case eFovv:
				param_holder = getParams(input_params,1);
				fovv = param_holder[0];
				if(fovv > 180 || fovv <= 0){
					error("vertical field of view must be a postive value less than or equal to 180 degrees");
				}
				delete [] param_holder;
				break;
			case eImsize:
				param_holder = getParams(input_params,2);
				imsize[0] = param_holder[0];
				imsize[1] = param_holder[1];
				if(imsize[0] <= 0 || imsize[1] <= 0){
					error("image width and height must be positive integers");
				}
				delete [] param_holder;
				break;
			case eBkgcolor:
				param_holder = getParams(input_params,3);
				for(int i = 0; i < 3 ; i++){
					if(param_holder[i] < 0.0 || param_holder[i] > 1.0){
						error("colors must be input as 'r g b' components between 0 and 1 inclusive");
					}
				}
				scene.setBkgColor(Color(param_holder[0],param_holder[1],param_holder[2]));
				delete [] param_holder;
				break;
			case eMtlcolor:
				param_holder = getParams(input_params,12);
				for(int i = 0; i < 6 ; i++){
					if(param_holder[i] < 0.0 || param_holder[i] > 1.0){
						error("colors must be input as 'r g b' components between 0 and 1 inclusive");
					}
				}
				for(int i = 6; i < 9 ; i++){
					if(param_holder[i] < 0.0 || param_holder[i] > 1.0){
						error("k values must be between 0 and 1 inclusive");
					}
				}
				scene.addMtlColor(new MtlColor(Color(param_holder[0],param_holder[1],param_holder[2]),
																				Color(param_holder[3],param_holder[4],param_holder[5]),
																				param_holder[6],
																				param_holder[7],
																				param_holder[8],
																				param_holder[9],
																				param_holder[10],
																				param_holder[11]));
				texture = false;
				delete [] param_holder;
				break;
			case eSphere:
				param_holder = getParams(input_params,4);
				scene.addObject(new Sphere(Vec3(param_holder[0],param_holder[1],param_holder[2]),
																		scene.m_colors.size() - 1,
																		scene.m_textures.size() - 1,
																		texture, param_holder[3]));
				if(param_holder[3] < 0.0){
					error("sphere's radius can not be negative");
				}
				delete [] param_holder;
				break;
			case eEllipsoid:
				param_holder = getParams(input_params,6);
				scene.addObject(new Ellipsoid(Vec3(param_holder[0],param_holder[1],param_holder[2]),
																			scene.m_colors.size() - 1,
																			scene.m_textures.size() - 1,
																			texture ,
																			Vec3(param_holder[3],
																			param_holder[4],
																			param_holder[5])));
				if(param_holder[3] < 0.0 || param_holder[4] < 0.0 || param_holder[5] < 0.0){
					error("ellipsoid can not have any negative radius");
				}
				delete [] param_holder;
				break;
			case eLight:
				param_holder = getParams(input_params,7);
				for(int i = 4; i < 7 ; i++){
					if(param_holder[i] < 0.0 || param_holder[i] > 1.0){
						error("colors must be input as 'r g b' components between 0 and 1 inclusive");
					}
				}
				if(param_holder[3] != 0 && param_holder[3] != 1){
					error("fourth argument for lights must be 0 or 1");
				}
				scene.addLight(new Light(Vec3(param_holder[0],param_holder[1],param_holder[2]),
																	param_holder[3],
																	Color(param_holder[4],param_holder[5],param_holder[6])));
				delete [] param_holder;
				break;
			case eVertex:
				param_holder = getParams(input_params,3);
				scene.addVertex(Vec3(param_holder[0],param_holder[1],param_holder[2]));
				delete [] param_holder;
				break;
			case eVertexNormal:
				param_holder = getParams(input_params,3);
				scene.addVertexNormal(Vec3(param_holder[0],param_holder[1],param_holder[2]));
				delete [] param_holder;
				break;
			case eFace:
				{
					string triangle;
					getline(input_params,triangle);
					int first = triangle.find_first_not_of(' ');
					triangle = triangle.substr(first);
					bool t_text(false), t_norm(false);
					stringstream ss,otherss,real;
					ss << triangle;
					otherss << triangle;
					int int_garb;
					char char_garb;
					ss >> int_garb >> char_garb;
					otherss >> int_garb >> char_garb;
					if(char_garb == '/'){
						ss >> char_garb;
						otherss >> int_garb;
						if(char_garb == '/'){
							t_norm = true;
						}
						else {
							t_text = true;
							otherss >> char_garb;
							if(char_garb == '/'){
								t_norm = true;
							}
						}
					}
					real << triangle;
					int vertices[3],tcs[3],norms[3];
					for(int i = 0 ; i < 3 ; i++){
						while(real.peek() == '/' || real.peek() == ' '){
							real.ignore();
						}
						real >> vertices[i];
						while(real.peek() == '/' || real.peek() == ' '){
							real.ignore();
						}
						if(t_text){
							real >> tcs[i];
						}
						while(real.peek() == '/' || real.peek() == ' '){
							real.ignore();
						}
						if(t_norm){
							real >> norms[i];
						}
					}
					scene.addObject(new Triangle(Vec3(),
																				scene.m_colors.size() - 1,
																				scene.m_textures.size() - 1,
																				texture ,
																				scene.m_vertices[vertices[0] - 1],
																				scene.m_vertices[vertices[1] - 1],
																				scene.m_vertices[vertices[2] - 1]));
					if(t_text){
						scene.m_objects[scene.m_objects.size() - 1]->addTCs(Vec3(scene.m_texture_coordinates[tcs[0]-1][0],
																																			scene.m_texture_coordinates[tcs[1]-1][0],
																																			scene.m_texture_coordinates[tcs[2]-1][0]),
																																Vec3(scene.m_texture_coordinates[tcs[0]-1][1],
																																			scene.m_texture_coordinates[tcs[1]-1][1],
																																			scene.m_texture_coordinates[tcs[2]-1][1]));
					}
					if(t_norm){
						scene.m_objects[scene.m_objects.size() - 1]->addNorms(scene.m_vertex_normals[norms[0] - 1],
																																	scene.m_vertex_normals[norms[1] - 1],
																																	scene.m_vertex_normals[norms[2] - 1]);
					}
				}
				break;
			case eTexture:
				{
					Color** texture_temp;
					string texture_file;
					input_params >> texture_file;
					ifstream texture_in;
					texture_in.open(texture_file.c_str());
					if(texture_in.fail()){
						error("texture file " + texture_file + " could not be opened");
					}
					// get rid of 'P3' using the string used to open the texture file
					texture_in >> texture_file;
					float* size;
					float max;
					size = getParams(texture_in,2);
					texture_in >> max;
					texture_temp = new Color*[(int)size[0]];
					for(int i = 0 ; i < (int)size[0] ; i++){
						texture_temp[i] = new Color[(int)size[1]];
					}
					for(int i = 0; i < (int)size[1] ; i++){
						for(int j = 0; j < (int)size[0]; j++){
							param_holder = getParams(texture_in,3);
							texture_temp[j][i] = Color(param_holder[0]/max,param_holder[1]/max,param_holder[2]/max);
							delete [] param_holder;
						}
					}
					scene.addTexture(texture_temp);
					scene.addTextureSize(size);
				}
				texture = true;
				break;
			case eTextureCoordinate:
				param_holder = getParams(input_params,2);
				scene.addTextureCoordinate(param_holder);
				break;
			case eParallel:
				parallel = true;
				break;
			default:
				error("unknown keyword " + keyword_check);
				break;
		}
	}
	input_params.close();

	float aspect_ratio = (float)imsize[0] / (float)imsize[1];

	// create arrays to store output image colors in
	output_image = new Color*[imsize[0]];
	for(int i = 0 ; i < imsize[0] ; i++){
		output_image[i] = new Color[imsize[1]];
	}

	// calculate and normalize u and v
	Vec3 u = cross(viewdir,updir);
	u.normalize();
	Vec3 v = cross(u,viewdir);
	v.normalize();

	// determine height and width of viewing window
	float h = (2 * distance) * (tan((fovv*(M_PI / 180.0))/2));
	float w = h * aspect_ratio;

	// determine the viewing window corners
	if(parallel){
		distance = 0;
	}
	ul = eye + (distance * viewdir) + ((h / 2.0) * v) - ((w / 2.0) * u); // ul = view_origin + d⋅n + h/2⋅v – w/2⋅u
	ur = eye + (distance * viewdir) + ((h / 2.0) * v) + ((w / 2.0) * u); // ur = view_origin + d⋅n + h/2⋅v + w/2⋅u
	ll = eye + (distance * viewdir) - ((h / 2.0) * v) - ((w / 2.0) * u); // ll = view_origin + d⋅n – h/2⋅v – w/2⋅u
	lr = eye + (distance * viewdir) - ((h / 2.0) * v) + ((w / 2.0) * u); // lr = view_origin + d⋅n – h/2⋅v + w/2⋅u

	// determine the change in x and y per ray
	Vec3 delta_x = (ur - ul) / (imsize[0] - 1);
	Vec3 delta_y = (ll - ul) / (imsize[1] - 1);

	// shoot rays into the environment and detect objects, changing the current pixel to the appropriate color
	for(int i = 0 ; i < imsize[1] ; i++){
		for(int j = 0 ; j < imsize[0] ; j++){
			// packet of info
			RayPayload payload;
			// current ray being sent into the scene
			Ray current;
			if(parallel){
				current = Ray((ul + (j*delta_x) + (i*delta_y)),viewdir);
			}
			else {
				current = Ray(eye,(ul + (j*delta_x) + (i*delta_y)) - eye);
			}
			current.normalize();
			Color pixel_color = scene.m_bkgcolor;
			TraceRay(current,scene,payload);
			if(payload.m_object_id != -1){
				pixel_color = ShadeRay(current,scene,payload,1,true);
			}
			// update current pixel with the final result for its color
			output_image[j][i] = pixel_color;
		}
	}

	// generate output file name
	char output_file_name[file_name_length + 1];
	for(int i = 0; i < file_name_length - 3; i++){
		output_file_name[i] = argv[1][i];
	}
	output_file_name[file_name_length - 3] = 'p';
	output_file_name[file_name_length - 2] = 'p';
	output_file_name[file_name_length - 1] = 'm';
	output_file_name[file_name_length] = '\0';

	// open output file and check for failure
	output_ppm.open(output_file_name);
	if(output_ppm.fail()){
		error("output file could not be opened");
	}

	// send image parameters to file
	output_ppm << "P3" << endl;
	output_ppm << imsize[0] << ' ' << imsize[1] << endl;
	output_ppm << 255 << endl;

	// generate each pixel of the image
	for(int i = 0; i < imsize[1]; i++){
		for(int j = 0; j < imsize[0] ; j++){
			output_ppm << output_image[j][i] * 255;
		}
	}

	output_ppm.close();

	// de-allocate output image array's memory
	for(int i = 0 ; i < imsize[0] ; i++){
		delete [] output_image[i];
	}
	delete [] output_image;

	return 0;

}

void TraceRay(Ray& ray, Scene& scene, RayPayload& payload){
	for(int i = 0 ; i < scene.m_objects.size() ; i++){
		if(scene.m_objects[i]->findIntersection(ray,payload)){
			payload.m_object_id = i;
		}
	}
}

Color ShadeRay(Ray& ray, Scene& scene, RayPayload& payload,int depth,bool outside){
	int num_lights = scene.m_lights.size();
	float epsilon = 0.0001;
	// calculate N and V vectors for all light computations
	Vec3 N = scene.m_objects[payload.m_object_id]->getNormal(ray,payload);
	Vec3 I = -1 * ray.getDir();
	Vec3 V = I;
	N.normalize();
	if(dot(N,I) < 0){
		N = -1 * N;
	}
	V.normalize();
	float red(0), green(0), blue(0);
	Color diffuse = scene.m_colors[payload.m_color_index]->m_d;
	// add Phong illumination if this is ray is on the outside of an object
	if(outside){

		// change diffuse to texture if it was a textured model
		if(payload.m_texture){
			float* UV = scene.m_objects[payload.m_object_id]->getTextureUV(payload);
			float u = UV[0];
			float v = UV[1];
			delete [] UV;
			float i = round(u * (scene.m_texture_sizes[payload.m_texture_index][0] - 1));
			float j = round(v * (scene.m_texture_sizes[payload.m_texture_index][1] - 1));
			diffuse = scene.m_textures[payload.m_texture_index][(int)i][(int)j];
		}

		// initialize ambiance
		red = scene.m_colors[payload.m_color_index]->m_ka * diffuse.getRed();
		green = scene.m_colors[payload.m_color_index]->m_ka * diffuse.getGreen();
		blue = scene.m_colors[payload.m_color_index]->m_ka * diffuse.getBlue();


		// go through each light and add its effect to the color values red, green, and blue
		for(int i = 0; i < num_lights; i++){
			Vec3 L = scene.m_lights[i]->getL(ray.getPos(payload.m_dist));
			Vec3 H = L + V;
			H.normalize();
			float shadow_effect = 1;
			float min_dist = -1;
			// make sure the light isn't obstructed by any other object
			RayPayload light_payload;
			for(int j = 0 ; j < scene.m_objects.size() ; j++){
				Ray light_ray(ray.getPos(payload.m_dist),L);
				light_ray = Ray(light_ray.getPos(epsilon),light_ray.getDir());
				scene.m_objects[j]->findIntersection(light_ray,light_payload);
			}
			// directional light
			if(scene.m_lights[i]->isDirectional()){
				if(light_payload.m_dist > 0){
					// add in shadow_effect of each intersecting object
					for(int k = 0; k < light_payload.m_intersect_colors.size() ; k++){
						shadow_effect *= (1 - scene.m_colors[light_payload.m_intersect_colors[k]]->m_alpha);
					}
				}
			}
			// point light
			else {
				// check if object was between light and intersection
				if(light_payload.m_dist > 0 && light_payload.m_dist < (sqrt(dot((ray.getPos(payload.m_dist)) - scene.m_lights[i]->getPos(),(ray.getPos(payload.m_dist)) - scene.m_lights[i]->getPos())))) {
					// add in shadow_effect of each intersecting object
					for(int k = 0; k < light_payload.m_intersect_colors.size() ; k++){
						shadow_effect *= (1 - scene.m_colors[light_payload.m_intersect_colors[k]]->m_alpha);
					}
				}
			}
			// add on added light for each component
			float NL = max((float)0,dot(N,L));
			float NH = max((float)0,dot(N,H));
			MtlColor* temp = scene.m_colors[payload.m_color_index];
			red += (shadow_effect * ((temp->m_kd * diffuse.getRed() * NL) + (temp->m_ks * temp->m_s.getRed() * (pow(NH,temp->m_n)))));
			green += (shadow_effect * ((temp->m_kd * diffuse.getGreen() * NL) + (temp->m_ks * temp->m_s.getGreen() * (pow(NH,temp->m_n)))));
			blue += (shadow_effect * ((temp->m_kd * diffuse.getBlue() * NL) + (temp->m_ks * temp->m_s.getBlue() * (pow(NH,temp->m_n)))));
		}
	}

	// add in a reflected and transparent light components if depth is within range
	if(depth <= 6){
		// reflected
		float F0 = pow((scene.m_colors[payload.m_color_index]->m_refraction - 1)/(scene.m_colors[payload.m_color_index]->m_refraction + 1),2);
		float Fr = F0 + ((1 - F0) * pow(1 - (dot(N,I)),5));
		float a = dot(N,V);

		Vec3 reflection_direction =(2 * (a * N)) - I;
		reflection_direction.normalize();
		Ray reflection_ray(payload.m_intersect,reflection_direction);
		reflection_ray = Ray(reflection_ray.getPos(epsilon),reflection_ray.getDir());
		RayPayload reflection_payload;
		Color reflection_color = scene.m_bkgcolor;
		TraceRay(reflection_ray,scene,reflection_payload);
		if(reflection_payload.m_object_id != -1){
			reflection_color = ShadeRay(reflection_ray,scene,reflection_payload,depth+1,outside);
		}
		Fr = pow(Fr,depth);
		red += Fr * reflection_color.m_red;
		green += Fr * reflection_color.m_green;
		blue += Fr * reflection_color.m_blue;


		// transparent
		float ni, nt;
	  if(outside){
			ni = 1.0;
			nt = scene.m_colors[payload.m_color_index]->m_refraction;
		}
		else{
			ni = scene.m_colors[payload.m_color_index]->m_refraction;
			nt = 1.0;
		}
		float TIRcheck = 1 - ((pow(ni/nt,2))*(1 - pow(dot(N,I),2)));
		if(TIRcheck >= 0){
			reflection_direction = (sqrt(1 - ((pow(ni/nt,2))*(1 - pow(dot(N,I),2)))) * (-1 * N)) + (((ni/nt) * (dot(N,I) * N)) - I);
			reflection_direction.normalize();
		  reflection_ray = Ray(payload.m_intersect,reflection_direction);
			reflection_ray = Ray(reflection_ray.getPos(epsilon),reflection_ray.getDir());
			reflection_payload = RayPayload();
			TraceRay(reflection_ray,scene,reflection_payload);
			reflection_color = scene.m_bkgcolor;
			if(reflection_payload.m_object_id != -1){
				reflection_color = ShadeRay(reflection_ray,scene,reflection_payload,depth+1,!outside);
			}
			red += (1 - Fr)  * (1 - scene.m_colors[payload.m_color_index]->m_alpha) * reflection_color.m_red;
			green += (1 - Fr) * (1 - scene.m_colors[payload.m_color_index]->m_alpha) * reflection_color.m_green;
			blue += (1 - Fr) * (1 - scene.m_colors[payload.m_color_index]->m_alpha) * reflection_color.m_blue;
		}
	}

	// return a color whose values are clamped between 0 and 1
	return Color(min((float)1.0,red),min((float)1.0,green),min((float)1.0,blue));
}

void error(string message){
	cerr << "**Error: " << message << endl;
	exit(1);
}

float* getParams(ifstream& in, int n){
	float *param_holder;
	param_holder = new float[n];
	for(int i = 0; i < n ; i++){
		in >> param_holder[i];
	}
	return param_holder;
}

string_code convertToEnum(string str) {
	if(str == "eye") return eEye;
	if(str == "viewdir") return eViewdir;
	if(str == "updir") return eUpdir;
	if(str == "fovv") return eFovv;
	if(str == "imsize") return eImsize;
	if(str == "bkgcolor") return eBkgcolor;
	if(str == "mtlcolor") return eMtlcolor;
	if(str == "sphere") return eSphere;
	if(str == "ellipsoid") return eEllipsoid;
	if(str == "light") return eLight;
	if(str == "v") return eVertex;
	if(str == "f") return eFace;
	if(str == "vn") return eVertexNormal;
	if(str == "texture") return eTexture;
	if(str == "vt") return eTextureCoordinate;
	if(str == "parallel") return eParallel;
	return eUnknown;
}
