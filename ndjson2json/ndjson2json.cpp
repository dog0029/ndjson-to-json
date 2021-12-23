#if(0) // 하나의 ndjson을 하나의 json으로 생성
#include <opencv2\core.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
	//.ndjson 파일 열기
	std::string path;
	std::cout << "input folder path : ";
	std::cin >> path;
	std::cout << "path : " << path << "\n\n";

	std::vector<cv::String> files;
	cv::glob(path + "/*.ndjson", files);

	std::vector<std::string> extensions;
	std::string line = "";
	int index = 0;
	int index1 = 0;
	int index2 = 0;

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

		std::ofstream jsonfile_out;
		jsonfile_out.open("out_json/" + filename_without_ext + ".json");
		if (!jsonfile_out.is_open())
		{
			std::cout << "cannot open output file!\n";
			return 0;
		}

		//총 몇 문장인지 조사
		if (ndjsonfile_in_tmp.is_open())
		{
			index1 = 0;
			
			while (!ndjsonfile_in_tmp.eof())
			{
				getline(ndjsonfile_in_tmp, line);
				index1++;
			}
		}

		if (ndjsonfile_in.is_open())
		{
			index2 = 0;
			
			//맨 처음에 [ 삽입
			jsonfile_out << "[" << std::endl;

			//문자열 조사
			while (!ndjsonfile_in.eof())
			{
				getline(ndjsonfile_in, line);

				//중간에 ]]]} 가 보이면 , 삽입 -> 문장의 끝에 , 삽입
				if (index2 < index1 - 1)
					jsonfile_out << line << "," << std::endl;
				else
					jsonfile_out << line << std::endl;
				
				index2++;
			}
			//맨 마지막에 ] 삽입
			jsonfile_out << "]" << std::endl;
		}
		ndjsonfile_in.close();
		ndjsonfile_in_tmp.close();
		jsonfile_out.close();

		index++;
		std::cout << index << " 번째 " << filename_without_ext << " complete!\n";
	}
	return 0;
}
#endif