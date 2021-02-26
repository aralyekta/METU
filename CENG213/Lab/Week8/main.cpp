#include "HashUtils.h"

// check add

int main() {
    vector<string> nameVector{"Ada Rodriguez","Rosa Jefferson","Jeffrey Mendez","Lester Hart","Eunice Moran","Ina Wilkins","Nettie Bowman","Belle Cole","Elizabeth Wilson","Blake Bush","Mabel Mason","Ora Weber","Rodney Love","Cole Ross","Max Kelly","Elnora Spencer","Adele Bridges","Norman Stevenson","Dora Flowers","Tillie Gomez","Carlos Gordon","Augusta Schmidt","Mike Holmes","Howard Fernandez","Mabelle Sutton","Leila Baldwin","Laura Duncan","Isaac Waters","Dorothy Maldonado","Maurice Howard","Jeffrey Ramsey","Maria Sherman","Sophia Norman","Louise Allison","Shane Atkins","Florence Pope","Connor Fleming","Marion Austin","Fred Fowler","Nancy Austin","Delia Soto","Mary Massey","Eugene Alvarado","Lucile Ruiz","Jerome Wilkins","Frank Colon","Chris Oliver","Lina Bradley","Lucille McBride","Gregory Mann","Johnny Lyons","Jayden Ward","Fred Stevenson","Jeff Pearson","Elnora Adams","Rosetta Brady","Virginia Williams","Bernice Drake","Marie Evans","Francis Doyle","Sally Francis","Mathilda Marshall","Abbie Olson","Hettie Clayton","Etta Shaw","Catherine Graves","Jim Carpenter","Leila Ward","Derrick Blake","Julian Parsons","Madge Collins","Nora Mitchell","Luke Sherman","Julia Jimenez","Glenn Harrison","Franklin Pierce","Susan Byrd","Ethan Oliver","Belle Little","Polly Castro","Lora Fitzgerald","Clara Freeman","Ricardo Lowe","Dean Bennett","Arthur Turner","Anne Kim","Calvin Ramirez","May Robertson","Stephen Nguyen","Gary McBride","Steve Gilbert","Augusta Brooks","Winnie Vasquez","Elnora Tran","Sylvia Baldwin","Chris Cooper","Ricardo Curry","Rosa Torres","Ann Malone","Robert Greene"};

    HashStringTable HT;

    HashUtils hu;

    //hu.addNameList(nameVector);
    
    hu.addName("1");
    
    hu.addName("2");
    hu.addName("3");
    hu.addName("4");
    hu.deleteName("1");
    hu.addName("1");
    
    hu.addName("5");
    hu.addName("6");
    hu.addName("7");
    
    hu.addName("8");
    hu.addName("9");
    hu.addName("10");
    hu.addName("11");
    hu.deleteName("5");
    hu.deleteName("7");
    hu.deleteName("10");
    
    hu.addName("12");
    hu.addName("13");
    hu.addName("14");
    hu.addName("15");
    hu.addName("16");
    hu.addName("17");
    hu.searchName("14");
    
    hu.report();
    return 0;
}