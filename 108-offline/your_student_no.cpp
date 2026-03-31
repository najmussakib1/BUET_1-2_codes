//Include header files as required
#include <iostream>
#include <string>

using namespace std;
//===============================================================
class PartyMember{
	int member_id; //a unique ID assigned to each member by the political party
	string name; //name of the member
	long asset_value; //net asset of the member
    string nominated_for;  //name of the constituency if this member is nominated by his party for running election 
    //You are not allowed to add any other member variable in this class

	public:		
		//Write a default constructor for this class. Initialize data members as deem appropriate.
        PartyMember(){
            member_id=0;
            name="default_member";
            asset_value=0;
            nominated_for="";
        }
        PartyMember(string n, long asset){
            member_id=0;
            name=n;
            asset_value=asset;
            nominated_for="";
        }
        PartyMember(const PartyMember & p){
            member_id = p.member_id;
            name = p.name;
            asset_value = p.asset_value;
            nominated_for = p.nominated_for;
        }
		void show_member_details(){
            cout<<"ID: "<<member_id<<", Name: "<<name<<", Asset: "<<asset_value;
            if(nominated_for!=""){
                cout<<", Constituency: "<<nominated_for;
            } 
            cout<<endl;           
		}
        void set_member_id(int id){
            member_id=id;
        }
        void remove_nomination(){
            nominated_for="";
        }
        string get_nominated(){
            return nominated_for;
        }
        void nominate(string constituency){
            nominated_for=constituency;
        }
        int get_id(){
            return member_id;
        }
};
//===============================================================
class PoliticalParty{
	string name; //name of the political party
	PartyMember* members[1000]; //Array of pointers to PartyMember objects; Allocate an object to a pointer when a member is added. Assume that there will be at most 1000 members in a party
	int member_count; //count of members in the party
    
    //Add other member variables as required and justified
    int next_member_id;

	public:		
		//Write a copy constructor for this class
        PoliticalParty(string n){
            name=n;
            member_count=0;
            next_member_id=1;
        }
        PoliticalParty(const PoliticalParty&p){
            name = p.name;
            member_count = p.member_count;
            for(int i=0;i<member_count;i++){
                members[i] = p.members[i];
            }
            next_member_id = p.next_member_id;
        }
                
        PartyMember search_member(string constituency){
            for(int i=0;i<member_count;i++){
                if(members[i]->get_nominated()==constituency){
                    return *members[i];
                }
            }
            PartyMember pm;
            return pm;
        }

        void join_party(PartyMember m){
            members[member_count]=&m;
            member_count++;
            members[member_count-1]->set_member_id(next_member_id);
            next_member_id++;
        }

		void join_party(PoliticalParty& pp){
            //Add all the members of pp to this party and remove them from pp. Assign ids sequentially to the new members in this party. When a member joins from one party to another, his nomination, if given, from the old party is automatically cancelled.
            for(int i=0;i<pp.member_count;i++){
                members[member_count]=pp.members[i];
                member_count++;
                members[member_count-1]->set_member_id(pp.members[i]->get_id());
                members[member_count-1]->remove_nomination();
            }
            for(int i=0;i<pp.member_count;i++){
                pp.members[i]=nullptr;
            }
            pp.member_count=0;
		}

        void leave_party(int id){
            //Remove the member with the given id from this party. Rearrange the list such that all the members are consecutive, i.e., there is no hole in the list. When a member leaves a party, his id is never reused.
            int which_idx = -1;
            for(int i=0;i<member_count;i++){
                if(members[i]->get_id()==id){
                    which_idx=i;
                    break;
                }
            }
            if(which_idx<0){
                return;
            }
            for(int i = which_idx+1;i<member_count;i++){
                members[i-1]=members[i];
            }
            members[member_count]=nullptr;
            cancel_nomination(id);
            member_count--;
		}
		
        void nominate_member(int id, string constituency){
            //Nominate the member with given id for the constituency  
            if(id<1){
                return;
            }
            for(int i=0;i<member_count;i++){
                if(members[i]->get_id()==id){
                    members[i]->nominate(constituency);
                    return;
                }
            }              
        }

        void show_nominated_members(){
            cout<<"Nominated Members of "<<name<<":"<<endl;
            for(int i=0;i<member_count;i++){
                if(members[i]->get_nominated()!=""){
                    members[i]->show_member_details();
                }
            }                     
		}

        void cancel_nomination(int id){		
            int which_idx = -1;
            for(int i=0;i<member_count;i++){
                if(members[i]->get_id()==id){
                    which_idx=i;
                    break;
                }
            }
            if(which_idx<0){
                return;
            }
            members[which_idx]->nominate("");      
            cout<<"Nomination cancelled for member ID: "<<which_idx<<endl;                   
		}

        PoliticalParty form_new_party(string name){	
            //Form a new party with the members who have been denied nomination	from this party  
            PoliticalParty new_party(name);    
            for(int i=0;i<member_count;i++){
                if(members[i]->get_nominated()==""){
                    cout<<"leaving:"<<members[i]->get_id()<<endl;
                    new_party.join_party(*members[i]);
                    leave_party(members[i]->get_id());
                    i--;
                }
            }      
            return new_party;
		}

        void show_all_members(){
            cout<<"Members of "<<name<<":"<<endl;
            if(member_count==0){
                cout<<"No members found."<<endl;
                return;
            }
            for(int i=0;i<member_count;i++){
                members[i]->show_member_details();
            }           
		}

        //Add any other helper function as required and justified
};
//=======================================
int main(){
    PartyMember abc1("Mr. A", 100000000);
    PartyMember abc2("Mr. B", 4000000);
    PartyMember abc3("Mr. C",20000000);
	PoliticalParty p1("ABC");
	p1.join_party(abc1);
	p1.join_party(abc2);
    p1.join_party(abc3);
	p1.show_all_members();

    p1.nominate_member(1,"DHK-10");
    PartyMember pm=p1.search_member("DHK-10");
    cout<<endl<<"Details of the member nominated for DHK-10 constituency:"<<endl;
    pm.show_member_details();

    p1.nominate_member(2,"CUM-3");
    p1.nominate_member(3,"SYL-1");
    p1.show_nominated_members();

    PartyMember xyz1("Mr. X", 1000000);
	PartyMember xyz2("Mr. Y", 3000000);
    	
    PoliticalParty p2("XYZ"); 
    p2.join_party(xyz1);
	p2.join_party(xyz2);
    p2.show_all_members();
    
    p1.join_party(p2);
    p1.show_all_members();
    p2.show_all_members();
    
    PartyMember xyz3("Mr. Z",5000000);
    p2.join_party(xyz3);
    p2.show_all_members();
	
    p1.cancel_nomination(1);
    p1.cancel_nomination(3);
    p1.nominate_member(4,"CUM-3");
    p1.nominate_member(5,"SYL-1");
    p1.show_nominated_members();    
    
    PoliticalParty p3=p1.form_new_party("Renegades");
    p1.show_all_members();
    p3.show_all_members();    
}

/* Expected Output
Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000
ID: 2, Name: Mr. B, Asset: 4000000
ID: 3, Name: Mr. C, Asset: 20000000

Details of the member nominated for DHK-10 constituency:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10

Nominated Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 3, Name: Mr. C, Asset: 20000000, Constituency: SYL-1

Members of XYZ:
ID: 1, Name: Mr. X, Asset: 1000000
ID: 2, Name: Mr. Y, Asset: 3000000

Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 3, Name: Mr. C, Asset: 20000000, Constituency: SYL-1
ID: 4, Name: Mr. X, Asset: 1000000
ID: 5, Name: Mr. Y, Asset: 3000000

Members of XYZ:
No members found.

Members of XYZ:
ID: 3, Name: Mr. Z, Asset: 5000000

Nominated Members of ABC:
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 4, Name: Mr. X, Asset: 1000000, Constituency: CUM-3
ID: 5, Name: Mr. Y, Asset: 3000000, Constituency: SYL-1

Members of ABC:
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 4, Name: Mr. X, Asset: 1000000, Constituency: CUM-3
ID: 5, Name: Mr. Y, Asset: 3000000, Constituency: SYL-1

Members of Renegades:
ID: 1, Name: Mr. A, Asset: 100000000
ID: 2, Name: Mr. C, Asset: 20000000
*/