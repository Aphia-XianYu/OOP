#pragma once
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include<type_traits>
using namespace tinyxml2;
namespace XianYu_Serialize_xml{
	
	template<typename T>
	void write_xml(const T& value, XMLElement*& item) {
		item->SetAttribute("val", value);
	}
	template<>
	void write_xml(const std::string& value, XMLElement*& item) {
		item->SetAttribute("val", value.c_str());
	}
	template<>
	void write_xml(const bool& value, XMLElement*& item) {
		if (value == true)
			item->SetAttribute("val", "true");
		else
			item->SetAttribute("val", "false");
	}

	template <typename T>
	void serialize_xml(const T& value, const std::string& name, const std::string& filename) {

		XMLDocument doc;
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);

		XMLElement* element = doc.NewElement(name.c_str());
		element->SetText(std::to_string(value).c_str());
		root->InsertEndChild(element);

		doc.SaveFile(filename.c_str());

	}
	void serialize_xml(const std::string& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);

		XMLElement* element = doc.NewElement(name.c_str());
		element->SetText(value.c_str());
		root->InsertEndChild(element);

		doc.SaveFile(filename.c_str());
	}
	template<typename T>
	void serialize_xml(const std::vector<T>& value, const std::string& name, const std::string &filename) {
		XMLDocument doc;
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);
		XMLElement* collectionElement = doc.NewElement(name.c_str());

		for (const auto& it : value) {
			XMLElement* childElement = doc.NewElement("item");
			write_xml(it, childElement); 
			collectionElement->InsertEndChild(childElement);
		}

		root->InsertEndChild(collectionElement);
		doc.SaveFile(filename.c_str());

	}
	template<typename T>
	void serialize_xml(const std::list<T>& value, const std::string& name,const std::string& filename) {

		XMLDocument doc;
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);
		XMLElement* collectionElement = doc.NewElement(name.c_str());

		for (const auto& it : value) {
			XMLElement* childElement = doc.NewElement("item");
			write_xml(it, childElement);
			collectionElement->InsertEndChild(childElement);
		}

		root->InsertEndChild(collectionElement);
		doc.SaveFile(filename.c_str());
	}
	template<typename T>
	void serialize_xml(const std::set<T>& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);
		XMLElement* collectionElement = doc.NewElement(name.c_str());

		for (const auto& it : value) {
			XMLElement* childElement = doc.NewElement("item");
			write_xml(it, childElement);
			collectionElement->InsertEndChild(childElement);
		}
		root->InsertEndChild(collectionElement);
		doc.SaveFile(filename.c_str());
	}
	template<typename T,typename U>
	void serialize_xml(const std::pair<T,U>& value, const std::string& name,const std::string& filename) {

		XMLDocument doc;
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);
		XMLElement* collectionElement = doc.NewElement(name.c_str());

		XMLElement* FirstElement = doc.NewElement("first");
		write_xml(value.first, FirstElement);
		collectionElement->InsertEndChild(FirstElement);
		XMLElement* SecondElement = doc.NewElement("second");
		write_xml(value.second, SecondElement);
		collectionElement->InsertEndChild(SecondElement);

		root->InsertEndChild(collectionElement);
		doc.SaveFile(filename.c_str());
	}
	template<typename T, typename U>
	void serialize_xml(const std::map<T, U>& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;
		XMLElement* root = doc.NewElement("serialization");
		doc.InsertFirstChild(root);
		XMLElement* collectionElement = doc.NewElement(name.c_str());

		for (const auto& it : value) {
			XMLElement* keyElement = doc.NewElement("key");
			write_xml(it.first, keyElement);
			collectionElement->InsertEndChild(keyElement);

			XMLElement* valueElement = doc.NewElement("value");
			write_xml(it.second, valueElement);
			collectionElement->InsertEndChild(valueElement);
		}
		root->InsertEndChild(collectionElement);
		doc.SaveFile(filename.c_str());
	}
	
	template<typename T>
	bool trans_value(T& value, const std::string& item) {

		if constexpr (std::is_same_v<T, int>) {
			value = std::stoi(item);
		}
		else if constexpr (std::is_same_v<T, double>) {
			value = std::stod(item);
			std::cout << value << "from trans" << std::endl;
		}
		else if constexpr (std::is_same_v<T, float>) {
			value = std::stof(item);
		}
		else if constexpr (std::is_same_v<T, std::string>) {
			value = item;
		}
		else if constexpr (std::is_same_v<T, bool>) {
			value = (item == "1") ? true : false;
		}
		else if constexpr (std::is_same_v<T, size_t>) {
			value = static_cast<size_t>(std::stoull(item));
		}
		else {
			return false;
		}

		return true;
	}

	template<typename T>
	 void read_xml(T& value, XMLElement*& item) {
		std::string val = item->Attribute("val");
		if (!val.empty()) {
			trans_value(value, val);
		}
	}
	template <typename T>
	bool deserialize_xml(T& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;

		if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
			std::cerr << "Failed to load XML file" << std::endl;
			return false;
		}

		XMLElement* root = doc.FirstChildElement("serialization");
		if (!root) {
			std::cerr << "No root element found" << std::endl;
			return false;
		}

		XMLElement* element = root->FirstChildElement(name.c_str());
		if (!element || !element->GetText()) {
			std::cerr << "No element found with name: " << name << std::endl;
			return false;
		}

		std::string item = element->GetText();
		
		if (trans_value(value, item))
			return true;
		else
			return false;
	
		
	}
	template <typename T>
	bool deserialize_xml(std::vector<T>& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;
		value.clear();
		if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
			std::cerr << "Failed to load XML file" << std::endl;
			return false;
		}

		XMLElement* root = doc.FirstChildElement("serialization");
		if (!root) {
			std::cerr << "No root element found" << std::endl;
			return false;
		}

		XMLElement* Vecelement = root->FirstChildElement(name.c_str());
		if (!Vecelement ) {
			std::cerr << "No element found with name: " << name << std::endl;
			return false;
		}

		for (XMLElement* itemElement = Vecelement->FirstChildElement(); itemElement; itemElement = itemElement->NextSiblingElement()) {
			if (std::string_view(itemElement->Name()) != "item")
				continue;

			std::string attrVal = itemElement->Attribute("val");
			T VecVal;
			trans_value(VecVal, attrVal);
			value.emplace_back(VecVal);
		}

		return true;
		

	}
	template <typename T>
	bool deserialize_xml(std::list<T>& value,const std::string& name,const std::string& filename){
		XMLDocument doc;
		value.clear();
		if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
			std::cerr << "Failed to load XML file" << std::endl;
			return false;
		}

		XMLElement* root = doc.FirstChildElement("serialization");
		if (!root) {
			std::cerr << "No root element found" << std::endl;
			return false;
		}

		XMLElement* ListElement = root->FirstChildElement(name.c_str());
		if (!ListElement) {
			std::cerr << "No element found with name: " << name << std::endl;
			return false;
		}

		for (XMLElement* itemElement = ListElement->FirstChildElement(); itemElement; itemElement = itemElement->NextSiblingElement()) {
			if (std::string_view(itemElement->Name()) != "item")
				continue;

			std::string attrVal = itemElement->Attribute("val");
			T VecVal;
			trans_value(VecVal, attrVal);
			value.emplace_back(VecVal);
		}

		return true;


	}
	template <typename T>
	bool deserialize_xml(std::set<T>& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;
		value.clear();
		if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
			std::cerr << "Failed to load XML file" << std::endl;
			return false;
		}

		XMLElement* root = doc.FirstChildElement("serialization");
		if (!root) {
			std::cerr << "No root element found" << std::endl;
			return false;
		}

		XMLElement* SetElement = root->FirstChildElement(name.c_str());
		if (!SetElement) {
			std::cerr << "No element found with name: " << name << std::endl;
			return false;
		}

		for (XMLElement* itemElement = SetElement->FirstChildElement(); itemElement; itemElement = itemElement->NextSiblingElement()) {
			if (std::string_view(itemElement->Name()) != "item")
				continue;

			std::string attrVal = itemElement->Attribute("val");
			T VecVal;
			trans_value(VecVal, attrVal);
			value.insert(VecVal);
		}

		return true;


	}
	template <typename T,typename U>
	bool deserialize_xml(std::map<T,U>& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;
		value.clear();
		if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
			std::cerr << "Failed to load XML file" << std::endl;
			return false;
		}

		XMLElement* root = doc.FirstChildElement("serialization");
		if (!root) {
			std::cerr << "No root element found" << std::endl;
			return false;
		}

		XMLElement* MapElement = root->FirstChildElement(name.c_str());
		if (!MapElement) {
			std::cerr << "No element found with name: " << name << std::endl;
			return false;
		}

		std::string keyAttr;
		std::string valAttr;
		T key;
		U val;

		for (XMLElement* itemElement = MapElement->FirstChildElement(); itemElement; itemElement = itemElement->NextSiblingElement()) {
			// 检索键、检索值，进行键值对的组装
			if (std::string_view(itemElement->Name()) == "key") {
				keyAttr = itemElement->Attribute("val");
				trans_value(key, keyAttr);
			}
			else if (std::string_view(itemElement->Name()) == "value") {
				valAttr = itemElement->Attribute("val");
				trans_value(val, valAttr);
				value[key] = val;
			}
			else
				continue;
		}


		return true;


	}

	template <typename T, typename U>
	bool deserialize_xml(std::pair<T, U>& value, const std::string& name, const std::string& filename) {
		XMLDocument doc;
		if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
			std::cerr << "Failed to load XML file" << std::endl;
			return false;
		}

		XMLElement* root = doc.FirstChildElement("serialization");
		if (!root) {
			std::cerr << "No root element found" << std::endl;
			return false;
		}

		XMLElement* PairElement = root->FirstChildElement(name.c_str());
		if (!PairElement) {
			std::cerr << "No element found with name: " << name << std::endl;
			return false;
		}

		std::string firstAttr;
		std::string secondAttr;
		T first;
		U second;

		for (XMLElement* itemElement = PairElement->FirstChildElement(); itemElement; itemElement = itemElement->NextSiblingElement()) {
			// 检索键、检索值，进行键值对的组装
			if (std::string_view(itemElement->Name()) == "first") {
				firstAttr = itemElement->Attribute("val");
				trans_value(first, firstAttr);
				value.first = first;
			}
			else if (std::string_view(itemElement->Name()) == "second") {
				secondAttr = itemElement->Attribute("val");
				trans_value(second, secondAttr);
				value.second = second;
			}
			else
				continue;
		}


		return true;


	}
	
	
}