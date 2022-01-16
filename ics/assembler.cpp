/*
 * @Author       : Chivier Humber
 * @Date         : 2021-08-30 15:10:31
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-11-23 15:34:30
 * @Description  : file content
 */
//Check all to be done content
//Date 2021/12/10
#include "assembler.h"
#include "fstream"
#include "iostream"
#include "bits/stdc++.h"
//#define lPseudo 1
//#define lComment -1
//#define lOperation 2
using namespace std;
void label_map_tp::AddLabel(const std::string &str, const value_tp &val) {
    labels_.insert(std::make_pair(str, val));
}

value_tp label_map_tp::GetValue(const std::string &str) const {
    // User (vAddress, -1) to represent the error case
    if (labels_.find(str) == labels_.end()) {
        // not found
        return value_tp(vAddress, -1);
    } else {
        return labels_.at(str);
    }
}

std::ostream &operator<<(std::ostream &os, const StringType &item) {
    switch (item) {
    case sComment:
        os << "Comment ";
        break;
    case sLabel:
        os << "Label";
        break;
    case sValue:
        os << "Value";
        break;
    case sOpcode:
        os << "Opcode";
        break;
    case sOprand:
        os << "Oprand";
        break;
    default:
        os << "Error";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const ValueType &val) {
    switch (val) {
    case vAddress:
        os << "Address";
        break;
    case vValue:
        os << "Value";
        break;
    default:
        os << "Error";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const value_tp &value) {
    if (value.type_ == vValue) {
        os << "[ " << value.type_ << " -- " << value.val_ << " ]";
    } else {
        os << "[ " << value.type_ << " -- " << std::hex << "0x" << value.val_ << " ]";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const label_map_tp &label_map) {
    for (auto item : label_map.labels_) {
        os << "Name: " << item.first << " " << item.second << std::endl;
    }
    return os;
}

void RecognizeNumberValue(std::string s, int &result) {
      for(int i=0;i<s.length();i++)
      {
      	if(!isdigit(s[i])){
      		s[i]=toupper(s[i]);
      	}
      }
      if (s[0] == 'X') {
        bool minus_flag = s[1] == '-' ? true : false;
        std::string num = minus_flag ? s.substr(2) : s.substr(1);

        //std::transform(num.begin(), num.end(), num.begin(), toupper);
        int sum = 0, weight = 1;
        for (int j = num.size() - 1; j >= 0; j--) {
            int factor;
            if (num[j] >= '0' && num[j] <= '9')
                factor = num[j] - '0';
            else if (num[j] >= 'A' && num[j] <= 'F')
                factor = num[j] - 'A' + 10;
            else
                return ;
            sum += factor * weight;
            weight *= 16;
        }
        int m=minus_flag ? -sum : sum;
        result+=m;
    } else if (s[0] == '#') {
        result+=atoi(s.substr(1).c_str());
    } else {
       result+=atoi(s.c_str());
    }
}

void NumberToAssemble(const int &number, std::string &nl) {
    // Convert the number into a 16 bit binary string
    // TO BE DONE
    //std::string nl;
    int num = number;
    std::string s;
    int flag=0;
    if(num<0){flag=1;
    num=-num-1;
    while (num) {
        s += (num % 2 ? '0' : '1');
        num /= 2;
    }
    }else{
    while (num) {
        s += (num % 2 ? '1' : '0');
        num /= 2;
    }}
    int length = s.size();
    if(!flag)
    for (int i = 0; i < 16 - length; i++) {
        s += '0';
    }else{
    for (int i = 0; i < 16 - length; i++) 
        s += '1';
    }
    std::reverse(s.begin(), s.end());
    nl+=s;
}

void NumbToAssemble(const std::string &number, std::string &res) {
    // Convert the number into a 16 bit binary string
    // You might use `RecognizeNumberValue` in this function
    // TO BE DONE
    std::string temp=number;
    int ll=0;
    RecognizeNumberValue(temp,ll);
    NumberToAssemble(ll,res);
    return;
}

void ConvertBin2Hex(std::string bin, std::string &res)  {
    // Convert the binary string into a hex string
    // TO BE DONE
    //std::string res;
    while(bin.length()%4!=0)
    {
		if(bin[0]-'0')
		{
			std::string m;m.push_back('1');
			bin.insert(0,m);
		}
		else{
			std::string m;m.push_back('0');
			bin.insert(0,m);
		}
    }
	for(int i=0;i<bin.length()/4;i++)
	{
		int num;
		num+=(bin[4*i]-'0')*8+(bin[4*i+1]-'0')*4+(bin[4*i+2]-'0')*2+bin[4*i+3]-'0';
		if(num<10)
		{res.push_back(num+'0');}
		if(num==10)
		{res.push_back('A');}
		if(num==11)
		{res.push_back('B');}
		if(num==12)
		{res.push_back('C');}
		if(num==13)
		{res.push_back('D');}
		if(num==14)
		{res.push_back('E');}
		if(num==15)
		{res.push_back('F');}
	}
	//return res;
}
//The transform functions seem to have no problem
int assembler::TranslateOprand(int current_address, std::string str, std::string &result, int opcode_length ) {
    // Translate the oprand
    Trim(str);
    auto item = label_map.GetValue(str);
	   //std::cout<<"item"<<item.getVal()<<endl;
	   //cout<<"str"<<str<<endl;
    if(!opcode_length){opcode_length=str.length();}
    if (!(item.getType() == vAddress && item.getVal() == -1)) {
        // str is a label
        // TO BE DONE
        //cout<<"found a label"<<endl;
        int label_address=item.getVal();
        //cout<<"label_address"<<label_address<<endl;
        int offset=label_address-current_address-1;
        //cout<<"ofset"<<offset<<endl;
        std::string comple_str;
        for (int i = 0; i < opcode_length; i++) {
            int mask = offset & (1 << i);
            comple_str += mask ? '1' : '0';
        }
        //comple_str += (offset >= 0 ? '0' : '1');
        std::reverse(comple_str.begin(), comple_str.end());
        //cout<<"com"<<comple_str<<endl;
        //comple_str=comple_str.substr(comple_str.length()-opcode_length,comple_str.length());
        result+=comple_str;
        return 1;
        //label part is not original   
    }
    if (str[0] == 'R') {
        // str is a register
        // TO BE DONE
        int regis_num = str[1] - '0';
        static const std::string regis_table[8] = {"000", "001", "010", "011",
                                                   "100", "101", "110", "111"};
        result+=regis_table[regis_num];
    } else {
        // str is an immediate number
        // TO BE DONE
        int num=0; RecognizeNumberValue(str,num);
        //cout<<"num"<<num<<endl;
        // to op_length's bits 2's complement
        std::string comple_str;
        for (int i = 0; i < opcode_length; i++) {
            int mask = num & (1 << i);
            comple_str += mask ? '1' : '0';
        }
        //comple_str += (num >= 0 ? '0' : '1');
        std::reverse(comple_str.begin(), comple_str.end());
        result+=comple_str;
    }
    return 1;
}
//Now there is no doubt
// TODO: add error line index
int assembler::assemble(std::string input_filename, std::string output_filename) {
    // assemble main function
    // parse program
    // store the original string
    std::vector<std::string> file_content;
    std::vector<std::string> origin_file;
    // store the tag for line
    std::vector<LineStatusType> file_tag;
    std::vector<std::string> file_comment;
    std::vector<int> file_address;
    int orig_address = -1;
    std::string line;
    std::ifstream input_file(input_filename);
    //std::cout<<input_file.is_open<<std::endl;
    if (input_file.is_open()) {
        // Scan #0:
        // Read file
        // Store comments
        int checkcount;
        while (std::getline(input_file, line)) {
           // cout<<"checkcout"<<checkcount++<<endl;
            // Remove the leading and trailing whitespace
            Trim(line);
            //cout<<"after trim is"<<line<<endl;
            if (line.size() == 0) {
                // Empty line
                continue;
            }
            std::string origin_line = line;
            // Convert `line` into upper case
            //What is convert line into upper case
            // TO BE DONE
            for(int i=0;i<line.length();i++)
            {
                if(isdigit(line[i])){continue;}
				line[i]=toupper(line[i]);
			}
            // Store comments
            //cout<<"origin_line is"<<line<<endl;
            auto comment_position = line.find(";");
            //cout<<comment_position<<endl;
            if (comment_position == std::string::npos) {
                // No comments here
                //printf("1");
                file_content.push_back(line);
                origin_file.push_back(origin_line);
                file_tag.push_back(lPending);
                file_comment.push_back("");
                file_address.push_back(-1);
                continue;
            } else {
                // Split content and comment
                // TO BE DONE
                std::string content_str;int mm;
                for(mm=0;mm<comment_position;mm++)
                {content_str.push_back(line[mm]);}
                std::string comment_str;
                int jj;
                for(jj=content_str.length();jj<line.length();jj++)
                {comment_str.push_back(line[jj]);}
                // Delete the leading whitespace and the trailing whitespace
                Trim(comment_str);
                Trim(content_str);
                //std::cout<<comment_str<<std::endl;
                //std::cout<<content_str<<std::endl;//These are to check
                // Store content and comment separately
                file_content.push_back(content_str);
                origin_file.push_back(origin_line);
                file_comment.push_back(comment_str);
                if (content_str.size() == 0) {
                    // The whole line is a comment
                    file_tag.push_back(lComment);
                } else {
                    file_tag.push_back(lPending);
                }
                file_address.push_back(-1);
            }
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
        // @ Input file read error
        return -1;
    }

    // Scan #1:
    // Scan for the .ORIG & .END pseudo code
    // Scan for jump label, value label, line comments
    //cout<<"enter Scan #1 criterion"<<endl;
    int line_address = -1;
    for (int line_index = 0; line_index < file_content.size(); ++line_index) {
        if (file_tag[line_index] == lComment) {
            // This line is comment
            //cout<<"comment line"<<endl;
            continue;
        }
        //cout<<"line_index is"<<line_index<<endl;
        auto line = file_content[line_index];
        //std::cout<<"line is"<<line<<std::endl;
        // * Pseudo Command
        if (line[0] == '.') {
            file_tag[line_index] = lPseudo;
            // This line is a pseudo instruction
            // Only .ORIG & .END are line-pseudo-command
            auto line_stringstream = std::istringstream(line);
            std::string pseudo_command;
            line_stringstream >> pseudo_command;
            //cout<<"pseudo"<<pseudo_command<<endl;
            if (pseudo_command == ".ORIG") {
                // .ORIG
                std::string orig_value;
                line_stringstream >> orig_value;
                RecognizeNumberValue(orig_value, orig_address);
                if (orig_address == std::numeric_limits<int>::max()) {
                    // @ Error address
                    cout<<"error address"<<endl;
                    return -2;
                }
                file_address[line_index] = -1;
                line_address = orig_address;
            } else if (pseudo_command == ".END") {
                // .END
                file_address[line_index] = -1;
                // If set line_address as -1, we can also check if there are programs after .END
                break;
            } else if (pseudo_command == ".STRINGZ") {
                file_address[line_index] = line_address;
                std::string word;
                line_stringstream >> word;
                if (word[0] != '\"' || word[word.size() - 1] != '\"') {
                    // @ Error String format error
                    cout<<"STRINGZ error input format"<<endl;
                    return -6;
                }
                //cout<<word<<endl;
                //cout<<word.size()<<endl;
                auto num_temp = word.size() - 1;
                line_address += num_temp;
            } else if (pseudo_command == ".FILL") {
                // TO BE DONE
                file_address[line_index] = line_address;
                std::string word;
                line_stringstream >> word;//word.erase(word.begin()+0);
                int temp;
		        RecognizeNumberValue(word, temp);
		        NumberToAssemble(temp,word);
                line_address+=1;
            } else if (pseudo_command == ".BLKW") {
                // TO BE DONE
                file_address[line_index] = line_address;
		        std::string word;
                line_stringstream >> word;
                int num_temp;
                RecognizeNumberValue(word, num_temp);
                if (num_temp == std::numeric_limits<int>::max()) {
                    // @ Error Invalid Number input @ BLKW
                    return -6;
                }
                if (num_temp > 65535 || num_temp < -65536) {
                    // @ Error Too large or too small value @ BLKW
                    return -7;
                }
                //cout<<"num_temp"<<num_temp<<endl;
                line_address += num_temp - 1;
            } else {
                // @ Error Unknown Pseudo command
                cout<<"unknow Pseudo command"<<endl;
                return -100;
            }
// Flaw no function to check error input number
            continue;
        }
        //cout<<"line_address is"<<line_address<<endl;
        if (line_address == -1) {
            // @ Error Program begins before .ORIG
            cout<<"Error Program begins before .ORIG"<<endl;
            return -3;
        }

        file_address[line_index] = line_address;
        line_address++;
        // Split the first word in the line
        auto line_stringstream = std::stringstream(line);
        std::string word;
        line_stringstream >> word;
        Trim(word);
        //cout<<"word is"<<word<<endl;
        auto label_name = word;
        if (IsLC3Command(word) != -1 || IsLC3TrapRoutine(word) != -1) {
            // * This is an operation line
            // TO BE DONE
           file_tag[line_index]=lOperation; 
           continue;
        }
        // * Label
        // Store the name of the label
        //auto label_name = word;
        // Split the second word in the line
        line_stringstream >> word;
        Trim(word);
        //cout<<"word2"<<word<<endl;
        if (IsLC3Command(word) != -1 || IsLC3TrapRoutine(word) != -1 ||
            word == "") {
            // a label used for jump/branch
            file_tag[line_index] = lOperation;
            //cout<<"lOpration skip"<<endl;
            label_map.AddLabel(label_name,value_tp(vAddress, file_address[line_index]));
        } else {
            file_tag[line_index] = lPseudo;
            if (word == ".FILL") {
                line_stringstream >> word;
                //cout<<"fill word"<<word<<endl;
                int num_temp=0; RecognizeNumberValue(word, num_temp);
                if (num_temp == std::numeric_limits<int>::max()) {
                    cout<<"Error Invalid Number input @ FILL"<<endl;
                    return -4;
                }
                if (num_temp > 65535 || num_temp < -65536) {
                     cout<<"@ Error Too large or too small value  @ FILL"<<endl;
                    return -5;
                }
                label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
            }
            if (word == ".BLKW") {
                // modify label map
                // modify line address
                // TO BE DONE
		label_map.AddLabel(label_name,value_tp(vAddress, line_address - 1));
                std::string word;
                line_stringstream >> word;
                //cout<<"blkw word"<<word<<endl;
                int num_temp=0; RecognizeNumberValue(word,num_temp);
                //cout<<"num_temp"<<endl;
                if (num_temp == std::numeric_limits<int>::max()) {
                    cout<<"@ Error Invalid Number input @ BLKW"<<endl;
                    return -6;
                }
                if (num_temp > 65535 || num_temp < -65536) {
                    cout<<"@ Error Too large or too small value @ BLKW"<<endl;
                    return -7;
                }
                line_address += num_temp-1;
            }
            if (word == ".STRINGZ") {
                // modify label map
                // modify line address
                // TO BE DONE
		        label_map.AddLabel(label_name,value_tp(vAddress, line_address - 1));
                std::string word;
                std::string temp;
                while(temp[temp.size()-1]!='\"'){
                line_stringstream >> temp;
                word+=temp;word+=' ';}
                word.erase(word.size()-1);
                //cout<<"stringz word"<<word<<endl;cout<<word.size()<<endl;
                if (word[0] != '\"' || word[word.size() - 1] != '\"') {
                    cout<<"@ Error String format error"<<endl;
                    return -6;
                }
                auto num_temp = word.size() - 1;
                line_address += num_temp - 1;
                //cout<<"line_address"<<line_address<<endl;
            }
        }
    }
    //cout<<"check symbol"<<endl;
    if (gIsDebugMode) {
        // Some debug information
        std::cout << std::endl;
        std::cout << "Label Map: " << std::endl;
        std::cout << label_map << std::endl;

        for (auto index = 0; index < file_content.size(); ++index) {
            std::cout << std::hex << file_address[index] << " ";
            std::cout << file_content[index] << std::endl;
        }
    }

    // Scan #2:
    // Translate
    //cout<<"Here comes the Scan2 part"<<endl;
    // Check output file
    if (output_filename == "") {
        output_filename = input_filename;
        if (output_filename.find(".") == std::string::npos) {
            output_filename = output_filename + ".asm";
        } else {
            output_filename = output_filename.substr(0, output_filename.rfind("."));
            output_filename = output_filename + ".asm";
        }
    }
    std::ofstream output_file;
    // Create the output file
    output_file.open(output_filename);
    if (!output_file) {
        // @ Error at output file
        cout<<"error at output file"<<endl;
        return -20;
    }

    for (int line_index = 0; line_index < file_content.size(); ++line_index) {
        //cout<<file_address[line_index]<<endl;
        if (file_address[line_index] == -1 || file_tag[line_index] == lComment) {
            // * This line is not necessary to be translated
            continue;
        }
        auto line = file_content[line_index];
        auto line_stringstream = std::stringstream(line);
        //cout<<"line is"<<line<<endl;
        //cout<<"file_tag"<<file_tag[line_index]<<endl;
        if (gIsDebugMode)
            output_file << std::hex << file_address[line_index] << ": ";
        if (file_tag[line_index] == lPseudo) {
            // Tra  nslate pseudo command
            std::string word;
            line_stringstream >> word;
            //cout<<"pseudo word"<<word<<endl;
            if (word[0] != '.') {
                // Fetch the second word
                // Eliminate the label
                line_stringstream >> word;
            }
            if (word == ".FILL") {
                std::string number_str;
                line_stringstream >> number_str;
                //number_str.erase(number_str.begin()+0);
                //cout<<"number_str for fill"<<number_str<<endl;
                std::string output_line;
                NumbToAssemble(number_str,output_line);
                if (gIsHexMode)
                    ConvertBin2Hex(output_line, output_line );
                //cout<<"output_line for FILL"<<output_line<<endl;
                output_file << output_line << std::endl;
            } else if (word == ".BLKW") {
                // Fill 0 here
                // TO BE DONE
                std::string output_line = "0000000000000000";
                if (gIsHexMode)
                    ConvertBin2Hex(output_line,output_line);

                std::string number_str;
                line_stringstream >> number_str;
                int number=0; RecognizeNumberValue(number_str,number);
                //cout<<"number"<<number<<endl;
                //cout<<"a outputline for BLKW"<<output_line<<endl;
                for (int i = 0; i < number; i++) {
                    output_file << output_line << std::endl;
                }
            } else if (word == ".STRINGZ") {
                // Fill string here
                // TO BE DONE
                std::string number_str;
                std::string temp;
                while(temp[temp.size()-1]!='\"'){
                line_stringstream >> temp;
                number_str+=temp;number_str+=' ';}
                number_str.erase(number_str.begin()+0);
                //cout<<"number_str for stringz"<<number_str<<endl;
                number_str.erase(number_str.end()-2);
                //cout<<"number_str for stringz"<<number_str<<endl;
		for(int i=0;i<number_str.length();i++){
		std::string number; 
		if(!isdigit(number_str[i])){number_str[i]=(int)number_str[i]+32;}
		//if(number_str[i]==' '){number_str[i]=(int)number_str[i];}
		//number.push_back(number_str[i]);
                std::string output_line;
                NumberToAssemble(number_str[i], output_line);
                if (gIsHexMode)
                    ConvertBin2Hex(output_line, output_line );
                //cout<<"output_line for stringz is"<<output_line<<endl;
                output_file << output_line << std::endl;}
            }
//This part I think has no problem
       continue;
        }
	//All done 
        if (file_tag[line_index] == lOperation) {
            //cout<<"check symbol"<<endl;
            std::string word;
            //int trap_tag;
            line_stringstream >> word;
            if (IsLC3Command(word) == -1 && IsLC3TrapRoutine(word) == -1) {
                // Eliminate the label
                line_stringstream >> word;
            }
            //int word_posi=line.find(' ');
            //word=line.substr(0,word_posi);
            //cout<<"word is"<<word<<endl;
            std::string result_line = "";
            auto command_tag = IsLC3Command(word);
            auto parameter_str = line.substr(line.find(word) + word.size());
            Trim(parameter_str);
            // Convert comma into space for splitting
            // TO BE DONE
            for(int i=0;i<parameter_str.length();i++)
            {
            if(parameter_str[i]==','){parameter_str[i]=' ';}
            }
             //cout<<"parameter_str"<<parameter_str<<endl;
            auto current_address = file_address[line_index];
            std::vector<std::string> parameter_list;
            auto parameter_stream = std::stringstream(parameter_str);
            //cout<<"command_tag"<<command_tag<<endl;
            while (parameter_stream >> word) {
                parameter_list.push_back(word);
            }
            auto parameter_list_size = parameter_list.size();
           //cout<<"command_tag is"<<command_tag<<endl;
            if (command_tag != -1) 
            {
                // This is a LC3 command
                switch (command_tag) {
                case 0:
                    // "ADD"
                    result_line += "0001";
                    if (parameter_list_size != 3) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0],result_line,0);
                    //cout<<parameter_list[1]<<endl;
                    TranslateOprand(current_address, parameter_list[1],result_line,0);
                    if (parameter_list[2][0] == 'R') {
                        // The third parameter is a register
                        result_line += "000";
                        //cout<<parameter_list[2]<<endl;
                        TranslateOprand(current_address, parameter_list[2],result_line,0);
                    } else {
                        // The third parameter is an immediate number
                        result_line += "1";
                        // std::cout << "hi " << parameter_list[2] << std::endl;
                        //cout<<parameter_list[2]<<endl;
                       TranslateOprand(current_address, parameter_list[2], result_line, 5);
                    }
                    break;
                case 1:
                    // "AND"
                    // TO BE DONE
                    result_line+="0101";
		    if(parameter_list_size!=3)
		{
			return -30;
		}
		//cout<<parameter_list[0]<<endl;
		    TranslateOprand(current_address, parameter_list[0],result_line,0);
		   //cout<<parameter_list[1]<<endl;
                    TranslateOprand(current_address, parameter_list[1],result_line, 0);
                    if (parameter_list[2][0] == 'R') {
                        // The third parameter is a register
                        result_line += "000";
                        //cout<<parameter_list[2]<<endl;
                        TranslateOprand(current_address, parameter_list[2],result_line,0);
                    } else {
                        // The third parameter is an immediate number
                        result_line += "1";
                        // std::cout << "hi " << parameter_list[2] << std::endl;
                        //cout<<parameter_list[2]<<endl;
                        TranslateOprand(current_address, parameter_list[2], result_line, 5);
                    }
                    break;
                case 2:
                    // "BR"
                    // TO BE DONE
                    result_line+="0000111";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0], result_line,9 );
                    break;
                case 3:
                    // "BRN"
                    // TO BE DONE
                    result_line+="0000100";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0], result_line, 9);
                    break;
                case 4:
                    // "BRZ"
                    // TO BE DONE
                    result_line+="0000010";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0],  result_line, 9);
                    break;
                case 5:
                    // "BRP"
                    // TO BE DONE
                    result_line+="0000001";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0], result_line, 9);
                    break;
                case 6:
                    // "BRNZ"
                    // TO BE DONE
                    result_line+="0000110";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0], result_line, 9);
                    break;
                case 7:
                    // "BRNP"
                    // TO BE DONE
                    result_line+="0000101";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0], result_line, 9);
                    break;
                case 8:
                    // "BRZP"
                    // TO BE DONE
                    result_line+="0000011";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                     TranslateOprand(current_address, parameter_list[0],  result_line, 9);
                    break;
                case 9:
                    // "BRNZP"
                    result_line += "0000111";
                    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0],  result_line, 9);
                    break;
                case 10:
                    // "JMP"
                    // TO BE DONE
                    result_line+="1100000";
                    //cout<<parameter_list[0]<<endl;
		    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    result_line+="000000";
                    break;
                case 11:
                    // "JSR"
                    // TO BE DONE
                    result_line+="01001";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
                    TranslateOprand(current_address, parameter_list[0],result_line ,11);
		    break;
                case 12:
                    // "JSRR"
                    // TO BE DONE
                    result_line+="0100000";
		    if (parameter_list_size != 1) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    //cout<<parameter_list[0]<<endl;
		    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    result_line+="000000";
                    break;
                case 13:
                    // "LD"
                    // TO BE DONE
                    result_line+="0010";
                    //cout<<parameter_list_size;
		    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
		    TranslateOprand(current_address, parameter_list[0],result_line, 0);
		    TranslateOprand(current_address, parameter_list[1],result_line, 9);
		    break;
                case 14:
                    // "LDI"
                    // TO BE DONE
                    result_line+="1010";
		    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    TranslateOprand(current_address, parameter_list[1],result_line, 9);
                    break;
                case 15:
                    // "LDR"
                    // TO BE DONE
                    result_line+="0110";
		    if (parameter_list_size != 3) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    TranslateOprand(current_address, parameter_list[1], result_line,0);
		            TranslateOprand(current_address, parameter_list[2],result_line, 6);
		    break;
                case 16:
                    // "LEA"
                    // TO BE DONE
                    result_line+="1110";
		    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0],result_line,0);
                    //cout<<"LEA LABEL is"<<parameter_list[1]<<endl;
                    TranslateOprand(current_address, parameter_list[1],result_line, 9);
                    break;
                case 17:
                    // "NOT"
                    // TO BE DONE
                    result_line+="1001";
		    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    TranslateOprand(current_address, parameter_list[1], result_line,0);
		    result_line+="111111";
		    break;
                case 18:
                    // RET
                    result_line += "1100000111000000";
                    if (parameter_list_size != 0) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    break;
                case 19:
                    // RTI
                    // TO BE DONE
                    result_line+="1000000000000000";
                    break;
                case 20:
                    // ST
                    result_line += "0011";
                    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    TranslateOprand(current_address, parameter_list[1],  result_line, 9);
                    break;
                case 21:
                    // STI
                    // TO BE DONE
                    result_line+="1011";
		    if (parameter_list_size != 2) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    TranslateOprand(current_address, parameter_list[1], result_line, 9);
                    break;
                case 22:
                    // STR
                    // TO BE DONE
                    result_line+="0111";
		    if (parameter_list_size != 3) {
                        // @ Error parameter numbers
                        return -30;
                    }
                    TranslateOprand(current_address, parameter_list[0], result_line,0);
                    TranslateOprand(current_address, parameter_list[1], result_line,0);
		    TranslateOprand(current_address, parameter_list[2],result_line, 6);
		    break;
                case 23:
                    // TRAP
                    // TO BE DONE
                    result_line += "11110000";
                        if (parameter_list_size != 1) {
                            // @ Error parameter numbers
                            return -30;
                        }
                        TranslateOprand(current_address, parameter_list[0],result_line , 8);
                        break;
                default:
                    // Unknown opcode
                    // @ Error
                    result_line+="1101";
                    break;
                }
            } 
            else{
                // This is a trap routine
                //cout<<parameter_list[0]<<endl;
                //command_tag = IsLC3TrapRoutine(parameter_list[0]);
                command_tag = IsLC3TrapRoutine(word);
                //cout<<"trap command_tag is"<<command_tag<<endl;
                switch (command_tag) {
                    case 0:
                    // x20
                    result_line += "1111000000100000";
                    break;
                    case 1:
                    // x21
                    result_line += "1111000000100001";
                    break;
                    case 2:
                    // x22
                    result_line += "1111000000100010";
                    break;
                    case 3:
                    // x23
                    result_line += "1111000000100011";
                    break;
                    case 4:
                    // x24
                    result_line += "1111000000100100";
                    break;
                    case 5:
                    // x25
                    result_line += "1111000000100101";
                    break;
                    default:
                    // @ Error Unknown command
                    return -50;
                }
            }
            
            if (gIsHexMode)
                ConvertBin2Hex(result_line, result_line );
            output_file << result_line << std::endl;
        }
    }

    // Close the output file
    cout<<"already created output file"<<endl;
    output_file.close();
    // OK flag
    return 0;
}
