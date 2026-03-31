#include <iostream>
#include <string>

using namespace std;

class PartyMember {
    int member_id;
    string name;
    long asset_value;
    string nominated_for;

public:
    PartyMember() {
        member_id = 0;
        name = "default_member";
        asset_value = 0;
        nominated_for = "";
    }
    PartyMember(string n, long asset) {
        member_id = 0;
        name = n;
        asset_value = asset;
        nominated_for = "";
    }
    // Standard Copy Constructor
    PartyMember(const PartyMember& p) {
        member_id = p.member_id;
        name = p.name;
        asset_value = p.asset_value;
        nominated_for = p.nominated_for;
    }

    void show_member_details() {
        cout << "ID: " << member_id << ", Name: " << name << ", Asset: " << asset_value;
        if (nominated_for != "") {
            cout << ", Constituency: " << nominated_for;
        }
        cout << endl;
    }

    void set_member_id(int id) {
        member_id = id;
    }
    void remove_nomination() {
        nominated_for = "";
    }
    string get_nominated() {
        return nominated_for;
    }
    void nominate(string constituency) {
        nominated_for = constituency; 
    }
    int get_id() {
        return member_id;
    }
};

class PoliticalParty {
    string name;
    PartyMember* members[1000];
    int member_count;
    int next_member_id;

public:
    PoliticalParty(string n) {
        name = n;
        member_count = 0;
        next_member_id = 1;
    }

    PoliticalParty(const PoliticalParty& p) {
        name = p.name;
        member_count = p.member_count;
        next_member_id = p.next_member_id;
        for (int i = 0; i < member_count; i++) {
            members[i] = new PartyMember(*p.members[i]);
        }
    }
    void join_party(PartyMember m) {
        members[member_count] = new PartyMember(m); 
        members[member_count]->set_member_id(next_member_id++);
        member_count++;
    }
    void join_party(PoliticalParty& pp) {
        for (int i = 0; i < pp.member_count; i++) {
            members[member_count] = pp.members[i];
            members[member_count]->set_member_id(next_member_id++);
            members[member_count]->remove_nomination();
            member_count++;
            pp.members[i] = nullptr; 
        }
        pp.member_count = 0;
    }

    void leave_party(int id) {
        int idx = -1;
        for (int i = 0; i < member_count; i++) {
            if (members[i]->get_id() == id) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            for (int i = idx; i < member_count - 1; i++) {
                members[i] = members[i + 1];
            }
            member_count--;
            members[member_count] = nullptr;
        }
    }

    void nominate_member(int id, string constituency) {
        for (int i = 0; i < member_count; i++) {
            if (members[i]->get_id() == id) {
                members[i]->nominate(constituency);
                return;
            }
        }
    }

    void cancel_nomination(int id) {
        for (int i = 0; i < member_count; i++) {
            if (members[i]->get_id() == id) {
                members[i]->remove_nomination();
                return;
            }
        }
    }

    PoliticalParty form_new_party(string n_name) {
        PoliticalParty new_party(n_name);
        for (int i = 0; i < member_count; i++) {
            if (members[i]->get_nominated() == "") {
                new_party.members[new_party.member_count] = members[i];
                new_party.members[new_party.member_count]->set_member_id(new_party.next_member_id++);
                new_party.member_count++;

                for (int j = i; j < member_count - 1; j++) {
                    members[j] = members[j + 1];
                }
                member_count--;
                i--;
            }
        }
        return new_party;
    }

    PartyMember search_member(string constituency) {
        for (int i = 0; i < member_count; i++) {
            if (members[i]->get_nominated() == constituency) {
                return *members[i];
            }
        }
        return PartyMember();
    }

    void show_all_members() {
        cout << "Members of " << name << ":" << endl;
        if (member_count == 0) cout << "No members found." << endl;
        for (int i = 0; i < member_count; i++) members[i]->show_member_details();
    }

    void show_nominated_members() {
        cout << "Nominated Members of " << name << ":" << endl;
        for (int i = 0; i < member_count; i++) {
            if (members[i]->get_nominated() != "") members[i]->show_member_details();
        }
    }
};
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