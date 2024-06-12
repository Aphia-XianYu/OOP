#pragma once
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include<type_traits>
#include<sstream>
using namespace tinyxml2;
namespace XianYu_Serialize_xml{

	class DataXML {
	public:
		/*
		一堆write，将doc作为公用对象，减少调用的开销*/
		template<typename T>
		void serialize_XML(const T& value, const std::string& name, const std::string& filename);
		template<typename T>
		bool deserialize_XML(T& value, const std::string& name, const std::string& filename);
	private:

		XMLDocument doc;

		template<typename T>
		void write_xml(const T& value, XMLElement*& item);
		template<>
		void write_xml(const std::string& value, XMLElement*& item);
		template<>
		void write_xml(const bool& value, XMLElement*& item);
		template<typename T>
		void write_xml(const std::vector<T>& value, XMLElement*& item);
		template<typename T>
		void write_xml(const std::list<T>& value, XMLElement*& item);
		template<typename T>
		void write_xml(const std::set<T>& value, XMLElement*& item);
		template<typename T, typename U>
		void write_xml(const std::pair<T, U>& value, XMLElement*& item);
		template<typename T, typename U>
		void write_xml(const std::map<T, U>& value, XMLElement*& item);
		template<typename T>
		T from_string(const std::string& s);
		template<typename T>
		void read_basic(T& value, XMLElement* element);
		template<typename T>
		void read_xml(T& value, XMLElement* element);
		template<>
		void read_xml(std::string& value, XMLElement* element);
		template<>
		void read_xml(bool& value, XMLElement* element);
		template<typename T>
		void read_xml(std::vector<T>& value, XMLElement* element);
		template<typename T>
		void read_xml(std::list<T>& value, XMLElement* element);
		template<typename T>
		void read_xml(std::set<T>& value, XMLElement* element);
		template<typename T,typename U>
		void read_xml(std::pair<T, U>& value, XMLElement* element);
		template<typename T,typename U>
		void read_xml(std::map<T, U>& value, XMLElement* element);

	};
	
	template<typename T>
	void DataXML::write_xml(const T& value, XMLElement*& item) {
		item->SetAttribute("val", value);
	}
	template<>
	void DataXML::write_xml(const std::string& value, XMLElement*& item) {
		item->SetAttribute("val", value.c_str());
	}
	template<>
	void DataXML::write_xml(const bool& value, XMLElement*& item) {
		if (value == true)
			item->SetAttribute("val", "true");
		else
			item->SetAttribute("val", "false");
	}
	template<typename T>
	void DataXML::write_xml(const std::vector<T>& value, XMLElement*& item) {
		for (const auto& it : value){
			XMLElement* childElement = doc.NewElement("item");
			write_xml(it, childElement);
			item->InsertEndChild(childElement);
	}
	}
	template<typename T>
	void DataXML::write_xml(const std::list<T>& value, XMLElement*& item ){
		for (const auto& it : value) {
			XMLElement* childElement = doc.NewElement("item");
			write_xml(it, childElement);
			item->InsertEndChild(childElement);
		}
	}
	template<typename T>
	void DataXML::write_xml(const std::set<T>& value, XMLElement*& item ) {
		for (const auto& it : value){
			XMLElement* childElement = doc.NewElement("item");
			write_xml(it, childElement);
			item->InsertEndChild(childElement);
		}
	}
	template<typename T,typename U>
	void DataXML::write_xml(const std::pair<T, U>& value, XMLElement*& item) {
		XMLElement* FisrtElement = doc.NewElement("first");
		write_xml(value.first, FisrtElement);
		item->InsertFirstChild(FisrtElement);
		XMLElement* SecondElement = doc.NewElement("second");
		write_xml(value.second, SecondElement);
		item->InsertEndChild(SecondElement);

	}
	template<typename T,typename U>
	void DataXML::write_xml(const std::map<T, U>& value, XMLElement*& item) {
		for (const auto& it : value) {
			XMLElement* keyElement = doc.NewElement("key");
			write_xml(it.first, keyElement);
			item->InsertEndChild(keyElement);
			XMLElement* valueElement = doc.NewElement("value");
			write_xml(it.second, keyElement);
			item->InsertEndChild(valueElement);
		}
	}

	template<typename T>
	void DataXML::serialize_XML(const T& value, const std::string& name, const std::string& filename) {
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);

		XMLElement* element = doc.NewElement(name.c_str());
		write_xml(value,element);
		root->InsertEndChild(element);

		doc.SaveFile(filename.c_str());

	}
	

	 template<typename T>
	 T DataXML::from_string(const std::string& s) {
		 std::istringstream iss(s);
		 T value;
		 iss >> value;
	 }
	 template<typename T>
	 void DataXML::read_basic(T& value, XMLElement* element) {
		 std::string text = element->Attribute("val");
		 if (!text.empty) {
			 value = from_string<T>(text);
		 }
		 else {
			 std::cerr << "Failed to get value" << std::endl;
		 }
	 }

	 template<typename T>
	 void DataXML::read_xml(T& value, XMLElement* element) {
		 read_basic(value, element);
	 }

	 template<>
	 void DataXML::read_xml(std::string& value, XMLElement* element) {
		 std::string text = element->Attribute("val");
		 if (!text.empty()) {
			 value = text;
		 }
	 }

	 template<>
	 void DataXML::read_xml(bool& value, XMLElement* element) {
		 std::string text = element->Attribute("val");
		 if (!text.empty()) {
			 value = (text == "true");
		 }
	 }

	 template <typename T>
	 void DataXML::read_xml(std::vector<T>& value, XMLElement* element) {
		 value.clear();
		 XMLElement* child = element->FirstChildElement("item");
		 while (child) {
			 T item;
			 read_xml(item, child);
			 value.push_back(item);
			 child = child->NextSiblingElement("item");
		 }
	 }

	 template <typename T>
	 void DataXML::read_xml(std::list<T>& value, XMLElement* element) {
		 value.clear();
		 XMLElement* child = element->FirstChildElement("item");
		 while (child) {
			 T item;
			 read_xml(item, child);
			 value.push_back(item);
			 child = child->NextSiblingElement("item");
		 }
	 }

	 template <typename T>
	 void DataXML::read_xml(std::set<T>& value, XMLElement* element) {
		 value.clear();
		 XMLElement* child = element->FirstChildElement("item");
		 while (child) {
			 T item;
			 read_xml(item, child);
			 value.insert(item);
			 child = child->NextSiblingElement("item");
		 }
	 }

	 template <typename T, typename U>
	 void DataXML::read_xml(std::pair<T, U>& value, XMLElement* element) {
		 XMLElement* firstElem = element->FirstChildElement("first");
		 XMLElement* secondElem = element->FirstChildElement("second");
		 if (firstElem) {
			 read_xml(value.first, firstElem);
		 }
		 if (secondElem) {
			 read_xml(value.second, secondElem);
		 }
	 }

	 template <typename T, typename U>
	 void DataXML::read_xml(std::map<T, U>& value, XMLElement* element) {
		 value.clear();
		 XMLElement* child = element->FirstChildElement("key");
		 while (child) {
			 T key;
			 U val;
			 read_xml(key, child);
			 XMLElement* valElement = child->NextSiblingElement("value");
			 if (valElement) {
				 read_xml(val, valElement);
				 value.insert(std::make_pair(key, val));
			 }
			 child = valElement ? valElement->NextSiblingElement("key") : nullptr;
		 }
	 }

	 template <typename T>
	 bool DataXML::deserialize_XML(T& value, const std::string& name, const std::string& filename) {
		 XMLDocument doc;

		 if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
			 std::cerr << "Failed to load XML file: " << filename << std::endl;
			 return false;
		 }

		 XMLElement* root = doc.FirstChildElement("serialization");
		 if (!root) {
			 std::cerr << "No root element found in XML" << std::endl;
			 return false;
		 }

		 XMLElement* element = root->FirstChildElement(name.c_str());
		 if (!element) {
			 std::cerr << "No element found with name: " << name << std::endl;
			 return false;
		 }

		 read_xml(value, element);
		 return true;
	 }

	 template<typename T>
	 bool deserialize_xml(T& value, const std::string& name, const std::string& filename) {
		 DataXML DX;
		 if (DX.deserialize_XML(value, name, filename))
			 return true;
		 else
			 return false;
	 }

	 template<typename T>
	 void serialize_xml(const T& value, const std::string& name, const std::string& filename) {
		 DataXML DX;
		 DX.serialize_XML(value, name, filename);
	 }

}