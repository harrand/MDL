#include "mdl.hpp"
#include <iostream>

#define TEST_STOP "stop"
#define TEST_INVALID "invalid"

std::string inputCommand(std::string cmd, MDLF mdlf)
{
	auto splitString = [](std::string s, char d) -> std::vector<std::string>{std::istringstream ss(s);std::string t;std::vector<std::string> sp;while(std::getline(ss, t, d))sp.push_back(t);return sp;};
	std::vector<std::string> splitCmd = splitString(cmd, ' ');
	std::string cmdName = splitCmd.at(0);
	if(cmdName == "stop" || cmdName == "exit")
		return TEST_STOP;
	else if(cmdName == "addTag")
	{
		if(splitCmd.size() < 3)
			return TEST_INVALID;
		std::string tagName = splitCmd.at(1);
		std::string tagValue = "";
		for(unsigned int i = 2; i < splitCmd.size(); i++)
			tagValue.append(" " + splitCmd.at(i));
		mdlf.addTag(tagName, tagValue);
		return "Added the tag named '" + tagName + "' with the value '" + tagValue + "'.\n";
	}
	else if(cmdName == "addSequence")
	{
		if(splitCmd.size() < 3)
			return TEST_INVALID;
		std::string seqName = splitCmd.at(1);
		std::vector<std::string> seq;
		for(unsigned int i = 2; i < splitCmd.size(); i++)
			seq.push_back(splitCmd.at(i));
		mdlf.addSequence(seqName, seq);
		std::ostringstream ss;
		ss << seq.size();
		return "Added the sequence named '" + seqName + "' with sequence-size " + ss.str() + ".\n";
	}
	else if(cmdName == "deleteTag")
	{
		if(splitCmd.size() < 2)
			return TEST_INVALID;
		std::string tagName = splitCmd.at(1);
		mdlf.deleteTag(tagName);
		return "Attempted to delete the tag named '" + tagName + "'.\n";
	}
	else if(cmdName == "deleteSequence")
	{
		if(splitCmd.size() < 2)
			return TEST_INVALID;
		std::string seqName = splitCmd.at(1);
		mdlf.deleteSequence(seqName);
		return "Attempted to delete the sequence named '" + seqName + "'.\n";
	}
	else if(cmdName == "getTag")
	{
		if(splitCmd.size() < 2)
			return TEST_INVALID;
		//todo: finish
	}
	else if(cmdName == "update")
	{
		mdlf.update();
		return "Updated.\n";
	}
}

int main(int argc, char** argv)
{
	std::string filename = "";
	if(argc < 2)
	{
		std::cout << "Did not receive a custom filename for the data file. Using 'test.mdl' as default.\n";
		filename = "test.mdl";
	}
	else
	{
		for(unsigned int i = 1; i < argc; i++)
			filename.append(argv[i]);
		std::cout << "Using '" << filename << "'.\n";
	}
	MDLF input = MDLF(RawFile(filename));
	std::string cmd, status;
	while(status != TEST_STOP)
	{
		std::cout << "Enter a command:\n";
		std::getline(std::cin, cmd);
		status = inputCommand(cmd, input);
		std::cout << "Status from last command: '" << status << "'.\n";
		//blah
	}
	return 0;
}