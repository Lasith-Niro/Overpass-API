#include <cmath>
#include <iostream>
#include <sstream>
#include "../../template_db/block_backend.h"
#include "../core/settings.h"
#include "around.h"
#include "bbox_query.h"
#include "id_query.h"
#include "item.h"
#include "query.h"
#include "print.h"

using namespace std;

template < class TStatement >
class SProxy
{
  public:
    SProxy() : stmt_(0) {}
    
    ~SProxy()
    {
      if (stmt_)
	delete stmt_;
    }
    
    SProxy& operator()(const string& k, const string& v)
    {
      attributes[k] = v;
      return *this;
    }
    
    TStatement& stmt()
    {
      if (!stmt_)
        stmt_ = new TStatement(0, attributes);
      
      return *stmt_;
    }
    
  private:
    TStatement* stmt_;
    map< string, string > attributes;
};

void perform_print(Resource_Manager& rman, string from = "_")
{
  SProxy< Print_Statement >()("order", "id")("from", from).stmt().execute(rman);
}

void perform_query(string type, string key, string value, string db_dir)
{
  try
  {
    Nonsynced_Transaction transaction(false, false, db_dir, "");
    Resource_Manager rman(transaction);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type);
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key)("v", value).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    perform_print(rman);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "a");
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key)("v", value).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "b");
      SProxy< Item_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("set", "a").stmt(), "");
      stmt1.stmt().execute(rman);
    }
    if ((rman.sets()["_"].nodes != rman.sets()["b"].nodes) ||
        (rman.sets()["_"].ways != rman.sets()["b"].ways) ||
        (rman.sets()["_"].relations != rman.sets()["b"].relations))
    {
      cout<<"Sets \"_\" and \"b\" differ:\n";
      perform_print(rman, "b");
    }
  }
  catch (File_Error e)
  {
    cerr<<"File error caught: "
    <<e.error_number<<' '<<e.filename<<' '<<e.origin<<'\n';
  }
}

void perform_query
    (string type, string key1, string value1, string key2, string value2,
     string db_dir)
{
  try
  {
    Nonsynced_Transaction transaction(false, false, db_dir, "");
    Resource_Manager rman(transaction);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type);
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      SProxy< Has_Kv_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("k", key2)("v", value2).stmt(), "");      
      stmt1.stmt().execute(rman);
    }
    perform_print(rman);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "a");
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "b");
      SProxy< Item_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("set", "a").stmt(), "");
      SProxy< Has_Kv_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("k", key2)("v", value2).stmt(), "");      
      stmt1.stmt().execute(rman);
    }
    if ((rman.sets()["_"].nodes != rman.sets()["b"].nodes) ||
        (rman.sets()["_"].ways != rman.sets()["b"].ways) ||
        (rman.sets()["_"].relations != rman.sets()["b"].relations))
    {
      cout<<"Sets \"_\" and \"b\" differ:\n";
      perform_print(rman, "b");
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "c");
      SProxy< Has_Kv_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("k", key2)("v", value2).stmt(), "");      
      stmt1.stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "d");
      SProxy< Item_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("set", "a").stmt(), "");
      SProxy< Item_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("set", "c").stmt(), "");
      stmt1.stmt().execute(rman);
    }
    if ((rman.sets()["_"].nodes != rman.sets()["d"].nodes) ||
        (rman.sets()["_"].ways != rman.sets()["d"].ways) ||
        (rman.sets()["_"].relations != rman.sets()["d"].relations))
    {
      cout<<"Sets \"_\" and \"d\" differ:\n";
      perform_print(rman, "d");
    }
  }
  catch (File_Error e)
  {
    cerr<<"File error caught: "
    <<e.error_number<<' '<<e.filename<<' '<<e.origin<<'\n';
  }
}

void perform_query
    (string type, string key1, string value1, string key2, string value2,
     string key3, string value3, string db_dir)
{
  try
  {
    Nonsynced_Transaction transaction(false, false, db_dir, "");
    Resource_Manager rman(transaction);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type);
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      SProxy< Has_Kv_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("k", key2)("v", value2).stmt(), "");
      SProxy< Has_Kv_Statement > stmt4;
      stmt1.stmt().add_statement(&stmt4("k", key3)("v", value3).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    perform_print(rman);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "a");
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "b");
      SProxy< Has_Kv_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("k", key2)("v", value2).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "c");
      SProxy< Item_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("set", "a").stmt(), "");
      SProxy< Item_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("set", "b").stmt(), "");
      SProxy< Has_Kv_Statement > stmt4;
      stmt1.stmt().add_statement(&stmt4("k", key3)("v", value3).stmt(), "");      
      stmt1.stmt().execute(rman);
    }
    if ((rman.sets()["_"].nodes != rman.sets()["c"].nodes) ||
        (rman.sets()["_"].ways != rman.sets()["c"].ways) ||
        (rman.sets()["_"].relations != rman.sets()["c"].relations))
    {
      cout<<"Sets \"_\" and \"c\" differ:\n";
      perform_print(rman, "c");
    }
  }
  catch (File_Error e)
  {
    cerr<<"File error caught: "
    <<e.error_number<<' '<<e.filename<<' '<<e.origin<<'\n';
  }
}

void perform_regex_query
    (string type, string key, string value, string key2, string regex2,
     string key3, string regex3, string db_dir)
{
  try
  {
    Nonsynced_Transaction transaction(false, false, db_dir, "");
    Resource_Manager rman(transaction);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type);
      SProxy< Has_Kv_Statement > stmt2;
      if (key != "")
        stmt1.stmt().add_statement(&stmt2("k", key)("v", value).stmt(), "");
      SProxy< Has_Kv_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("k", key2)("regv", regex2).stmt(), "");
      SProxy< Has_Kv_Statement > stmt4;
      if (key3 != "")
	stmt1.stmt().add_statement(&stmt4("k", key3)("regv", regex3).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    perform_print(rman);
  }
  catch (File_Error e)
  {
    cerr<<"File error caught: "
    <<e.error_number<<' '<<e.filename<<' '<<e.origin<<'\n';
  }
}

void perform_query_with_around
    (string id_type, string type, string key1, string value1, string db_dir, uint pattern_size,
     bool big_radius = false)
{
  string radius = "200.1";
  if (id_type == "node" && type == "way")
  {
    ostringstream out;
    if (big_radius)
      out<<(120.0/pattern_size)/360.0*40*1000*1000*cos(-10.0/90.0*acos(0))*0.5;
    else
      out<<(120.0/pattern_size)/360.0*40*1000*1000*cos(-10.0/90.0*acos(0))*0.1;
    radius = out.str();
  }
  else if (id_type == "node" && type == "relation")
  {
    ostringstream out;
    if (big_radius)
      out<<(120.0/pattern_size)/360.0*40*1000*1000*cos(-10.0/90.0*acos(0))*0.9;
    else
      out<<(120.0/pattern_size)/360.0*40*1000*1000*cos(-10.0/90.0*acos(0))*1.2;
    radius = out.str();
  }
  else if (id_type == "way")
  {
    ostringstream out;
    if (type == "node")
      out<<(120.0/pattern_size)/360.0*40*1000*1000*1.1;
    else
      out<<1;
    radius = out.str();
  }
  else if (id_type == "relation")
  {
    ostringstream out;
    if (type == "node")
      out<<(120.0/pattern_size)/360.0*40*1000*1000*1.1;
    else
      out<<1;
    radius = out.str();
  }
  
  try
  {
    Nonsynced_Transaction transaction(false, false, db_dir, "");
    Resource_Manager rman(transaction);
    {
      ostringstream buf;
      if (id_type == "node" && type == "node")
        buf<<(2*pattern_size*pattern_size + 1);
      else if (id_type == "node" && type == "relation")
      {
	if (big_radius)
	  buf<<(pattern_size*pattern_size + pattern_size*3/2 + 1);
	else
	  buf<<(pattern_size*pattern_size + 2);
      }
      else if (id_type == "way")
      {
	if (type == "node")
	  buf<<(pattern_size*pattern_size/2 + pattern_size/2 - 2 + 1);
	else
	  buf<<(2*(pattern_size*pattern_size/2 + pattern_size/2 - 2) - pattern_size + 1);
      }
      else if (id_type == "relation")
      {
	if (type == "node")
	  buf<<16;
	else
	  buf<<17;
      }
      else if (big_radius)
	buf<<(pattern_size*pattern_size + 2*pattern_size);
      else
	buf<<(pattern_size*pattern_size + pattern_size - 1);
      SProxy< Id_Query_Statement >()("type", id_type)("ref", buf.str()).stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type);
      SProxy< Has_Kv_Statement > stmt2;
      if (value1 != "")
        stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      else if (key1 != "")
	stmt1.stmt().add_statement(&stmt2("k", key1).stmt(), "");
      SProxy< Around_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("radius", radius).stmt(), "");      
      stmt1.stmt().execute(rman);
    }
    perform_print(rman);
    if (key1 == "")
      return;
    {
      ostringstream buf;
      if (id_type == "node" && type == "node")
	buf<<(2*pattern_size*pattern_size + 1);
      else if (id_type == "node" && big_radius)
	buf<<(pattern_size*pattern_size + 2*pattern_size);
      else
	buf<<(pattern_size*pattern_size + pattern_size - 1);
      SProxy< Id_Query_Statement >()("type", id_type)("ref", buf.str())("into", "a")
          .stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "b");
      SProxy< Has_Kv_Statement > stmt2;
      if (value1 != "")
        stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      else
	stmt1.stmt().add_statement(&stmt2("k", key1).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "c");
      SProxy< Item_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("set", "b").stmt(), "");
      SProxy< Around_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("radius", radius)("from", "a").stmt(), "");      
      stmt1.stmt().execute(rman);
    }
    if ((rman.sets()["_"].nodes != rman.sets()["c"].nodes) ||
        (rman.sets()["_"].ways != rman.sets()["c"].ways) ||
        (rman.sets()["_"].relations != rman.sets()["c"].relations))
    {
      cout<<"Sets \"_\" and \"c\" differ:\n";
      perform_print(rman, "c");
    }
  }
  catch (File_Error e)
  {
    cerr<<"File error caught: "
        <<e.error_number<<' '<<e.filename<<' '<<e.origin<<'\n';
  }
}

void perform_query_with_bbox
    (string type, string key1, string value1,
     string south, string north, string west, string east, string db_dir)
{
  try
  {
    Nonsynced_Transaction transaction(false, false, db_dir, "");
    Resource_Manager rman(transaction);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type);
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      SProxy< Bbox_Query_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("n", north)("s", south)("e", east)("w", west).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    perform_print(rman);
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "a");
      SProxy< Has_Kv_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("k", key1)("v", value1).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    {
      SProxy< Query_Statement > stmt1;
      stmt1("type", type)("into", "b");
      SProxy< Item_Statement > stmt2;
      stmt1.stmt().add_statement(&stmt2("set", "a").stmt(), "");
      SProxy< Bbox_Query_Statement > stmt3;
      stmt1.stmt().add_statement(&stmt3("n", north)("s", south)("e", east)("w", west).stmt(), "");
      stmt1.stmt().execute(rman);
    }
    if ((rman.sets()["_"].nodes != rman.sets()["b"].nodes) ||
      (rman.sets()["_"].ways != rman.sets()["b"].ways) ||
      (rman.sets()["_"].relations != rman.sets()["b"].relations))
    {
      cout<<"Sets \"_\" and \"b\" differ:\n";
      perform_print(rman, "b");
    }
  }
  catch (File_Error e)
  {
    cerr<<"File error caught: "
    <<e.error_number<<' '<<e.filename<<' '<<e.origin<<'\n';
  }
}

int main(int argc, char* args[])
{
  if (argc < 4)
  {
    cout<<"Usage: "<<args[0]<<" test_to_execute pattern_size db_dir\n";
    return 0;
  }
  string test_to_execute = args[1];
  uint pattern_size = 0;
  pattern_size = atoi(args[2]);
  
  cout<<
  "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<osm>\n";
  
  // Test queries for nodes.
  if ((test_to_execute == "") || (test_to_execute == "1"))
    // Test a key and value which appears only locally
    perform_query("node", "node_key_11", "node_value_2", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "2"))
    // Test a key and value which appears almost everywhere
    perform_query("node", "node_key_5", "node_value_5", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "3"))
    // Test a key only which has multiple values
    perform_query("node", "node_key_11", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "4"))
    // Test a key only which has only one value
    perform_query("node", "node_key_15", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "5"))
    // Test a key only which doesn't appear at all
    perform_query("node", "nowhere", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "6"))
    // Test a key intersected with a small key and value pair
    perform_query("node", "node_key_7", "", "node_key_11", "node_value_8", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "7"))
    // Test a key intersected with a large key and value pair
    perform_query("node", "node_key_7", "", "node_key_15", "node_value_15", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "8"))
    // Test a bbox combined with a local key-value pair
    perform_query_with_bbox("node", "node_key_11", "node_value_2",
			    "51.0", "51.2", "7.0", "8.0", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "9"))
    // Test a bbox combined with a global key-value pair
    perform_query_with_bbox("node", "node_key_5", "node_value_5",
			    "-10.0", "-1.0", "-15.0", "-3.0", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "10"))
    // Test a bbox combined with a global key-value pair
    perform_query_with_bbox("node", "node_key_7", "",
			    "-10.0", "-1.0", "-15.0", "-3.0", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "11"))
    // Test three key-values intersected
    perform_query("node", "node_key_5", "node_value_5", "node_key_7", "node_value_0",
		  "node_key_15", "node_value_15", args[3]);
		  
  // Test queries for ways.
  if ((test_to_execute == "") || (test_to_execute == "12"))
    // Test a key and value which appears only locally
    perform_query("way", "way_key_11", "way_value_2", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "13"))
    // Test a key and value which appears almost everywhere
    perform_query("way", "way_key_5", "way_value_5", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "14"))
    // Test a key only which has multiple values
    perform_query("way", "way_key_11", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "15"))
    // Test a key only which has only one value
    perform_query("way", "way_key_15", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "16"))
    // Test a key only which doesn't appear at all
    perform_query("way", "nowhere", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "17"))
    // Test a key intersected with a small key and value pair
    perform_query("way", "way_key_7", "", "way_key_11", "way_value_8", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "18"))
    // Test a key intersected with a large key and value pair
    perform_query("way", "way_key_7", "", "way_key_15", "way_value_15", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "19"))
    // Test three key-values intersected
    perform_query("way", "way_key_5", "way_value_5", "way_key_7", "way_value_0",
		  "way_key_15", "way_value_15", args[3]);

  // Test queries for relations.
  if ((test_to_execute == "") || (test_to_execute == "20"))
    // Test a key and value which appears only locally
    perform_query("relation", "relation_key_11", "relation_value_2", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "21"))
    // Test a key and value which appears almost everywhere
    perform_query("relation", "relation_key_2/4", "relation_value_1", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "22"))
    // Test a key only which has multiple values
    perform_query("relation", "relation_key_2/4", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "23"))
    // Test a key only which has only one value
    perform_query("relation", "relation_key_5", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "24"))
    // Test a key only which doesn't appear at all
    perform_query("relation", "nowhere", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "25"))
    // Test two key-values intersected. This tests also whether
    // relations with index zero appear in the results.
    perform_query("relation", "relation_key_2/4", "relation_value_0",
		  "relation_key_5", "relation_value_5", args[3]);

  if ((test_to_execute == "") || (test_to_execute == "26"))
    // Test an around combined with a local key-value pair
    perform_query_with_around("node", "node", "node_key_11", "", args[3], pattern_size);
  if ((test_to_execute == "") || (test_to_execute == "27"))
    // Test an around combined with a global key-value pair
    perform_query_with_around("node", "node", "node_key_7", "node_value_1", args[3], pattern_size);

  if ((test_to_execute == "") || (test_to_execute == "28"))
    // Test a bbox combined with a global key-value pair, yielding diagonal ways.
    perform_query_with_bbox("way", "way_key_5", "way_value_5",
			    "12.5", "35.0", "-15.0", "45.0", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "29"))
    // Test a bbox combined with a global key-value pair, yielding horizontal and vertical ways.
    perform_query_with_bbox("way", "way_key_5", "way_value_5",
			    "57.5", "80.0", "75.0", "105.0", args[3]);

  if ((test_to_execute == "") || (test_to_execute == "30"))
    // Test a bbox combined with a global key-value pair, yielding diagonal ways.
    perform_query_with_bbox("relation", "relation_key_2/4", "",
			    "12.5", "35.0", "-15.0", "45.0", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "31"))
    // Test a bbox combined with a global key-value pair, yielding horizontal and vertical ways.
    perform_query_with_bbox("relation", "relation_key_2/4", "",
			    "57.5", "80.0", "75.0", "105.0", args[3]);

  if ((test_to_execute == "") || (test_to_execute == "32"))
    // Test regular expressions: A simple string
    perform_regex_query("node", "", "", "node_key_11", "^node_value_2$", "", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "33"))
    // Test regular expressions: An extended regular expression
    perform_regex_query("node", "", "", "node_key_11", "^node_.?alue_2$", "", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "34"))
    // Test regular expressions: Two regular expressions
    perform_regex_query("relation", "", "",
			"relation_key_2/4", "^relation_.*_0$",
			"relation_key_5", "^relation_.*_5$", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "35"))
    // Test regular expressions: A regular expression and a key-value pair
    perform_regex_query("relation",
			"relation_key_2/4", "relation_value_0",
			"relation_key_5", "^relation_.*_5$", "", "", args[3]);
  if ((test_to_execute == "") || (test_to_execute == "36"))
    // Test regular expressions: A regular expression and a key only
    perform_regex_query("way", "way_key_7", "", "way_key_11", "^way_.*_8$", "", "", args[3]);

  if ((test_to_execute == "") || (test_to_execute == "37"))
    // Test an around collecting ways from nodes
    perform_query_with_around("node", "way", "", "", args[3], pattern_size);
  if ((test_to_execute == "") || (test_to_execute == "38"))
    // Test an around collecting ways from nodes
    perform_query_with_around("node", "way", "", "", args[3], pattern_size, true);

  if ((test_to_execute == "") || (test_to_execute == "39"))
    // Test an around collecting relations from nodes based on node membership
    perform_query_with_around("node", "relation", "", "", args[3], pattern_size);
  if ((test_to_execute == "") || (test_to_execute == "40"))
    // Test an around collecting relations from nodes based on way membership
    perform_query_with_around("node", "relation", "", "", args[3], pattern_size, true);

  if ((test_to_execute == "") || (test_to_execute == "41"))
    // Test an around collecting relations from nodes based on node membership
    perform_query_with_around("way", "node", "", "", args[3], pattern_size);
  if ((test_to_execute == "") || (test_to_execute == "42"))
    // Test an around collecting relations from nodes based on way membership
    perform_query_with_around("way", "way", "", "", args[3], pattern_size);
  
  if ((test_to_execute == "") || (test_to_execute == "43"))
    // Test an around collecting relations from nodes based on node membership
    perform_query_with_around("relation", "node", "", "", args[3], pattern_size);
  if ((test_to_execute == "") || (test_to_execute == "44"))
    // Test an around collecting relations from nodes based on way membership
    perform_query_with_around("relation", "way", "", "", args[3], pattern_size);
  
  cout<<"</osm>\n";
  return 0;
}
