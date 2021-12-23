#if(1) // 하나의 ndjson을 여러개의 json으로 생성
#include <opencv2\core.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

int main()
{
	//.ndjson 파일 열기
	std::string path;
	std::cout << "input folder path : ";
	std::cin >> path;				//띄어쓰기 무시
	//std::getline(std::cin, path);	//띄어쓰기 포함
	std::cout << "path : " << path << "\n\n";

	std::vector<cv::String> files;
	cv::glob(path + "/*.ndjson", files);

	std::vector<std::string> extensions;
	std::string line = "";
	int index = 0;

	for (auto &i : files)
	{
		int pos_filename = 0;
		if ((1 + i.find_last_of("\\")) < i.length()) pos_filename = 1 + i.find_last_of("\\");
		if ((1 + i.find_last_of("/")) < i.length()) pos_filename = std::max(pos_filename, 1 + (int)i.find_last_of("/"));
		std::string const filename = i.substr(pos_filename);
		std::string const filename_without_ext = filename.substr(0, filename.find_last_of("."));

		std::ifstream ndjsonfile_in;
		ndjsonfile_in.open(i);
		std::ifstream ndjsonfile_in_tmp;
		ndjsonfile_in_tmp.open(i);

		if (ndjsonfile_in.is_open())
		{
			int image_index = 1;
			//문자열 조사
			while (!ndjsonfile_in.eof())
			{
				if (image_index % 10000 == 0)
				{
					std::cout << image_index << " 번째 " << filename_without_ext << " converting start!\n";
				}
				
				std::stringstream ss;
				ss << "out_json2/" << filename_without_ext << "/" << filename_without_ext << "_"
					<< std::setw(6) << std::setfill('0') << image_index << ".json";
				std::string str = ss.str();

				std::ofstream jsonfile_out;
				jsonfile_out.open(str);
				if (!jsonfile_out.is_open())
				{
					std::cout << "cannot open output file!\n";
					return 0;
				}

				getline(ndjsonfile_in, line);

				//맨 처음에 [ 삽입
				jsonfile_out << "[" << std::endl;
				//중간에 ]]]} 가 보이면 , 삽입 -> 문장의 끝에 , 삽입
				jsonfile_out << line << std::endl;
				//맨 마지막에 ] 삽입
				jsonfile_out << "]" << std::endl;
				
				jsonfile_out.close();
				
				image_index++;
			}
		}
		ndjsonfile_in.close();
		ndjsonfile_in_tmp.close();

		index++;
		std::cout << index << " 번째 " << filename_without_ext << " complete!\n\n";
	}
	return 0;
}
#endif