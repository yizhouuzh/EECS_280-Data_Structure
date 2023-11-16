// Project UID db1f506d06d84ab787baf250c265e24e
#include "csvstream.h"
#include <cassert> 
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Classifier
{
private:
    int size = 0; //Number of posts
    int voc_size = 0;
    set<string> word_set;
    set<string> label_set;
    vector<string> post;
    vector<string> label;
    vector<set<string>> all_post;
    map<string, int> post_word;
    map<string, int> post_label;
    map<pair<string,string>, int> post_word_label;
public:
    int get_size() {
        return size;
    }
    int get_voc_size() {
        return voc_size;
    }
    string get_post(const int index) {
        return post[index];
    }
    string get_label(const int index) {
        return label[index];
    }
    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

    void get_data(csvstream& data)  {
        map<string, string> row;
        for (int i = 0; data >> row;  i++) {
            size++;
            post.push_back(row["content"]);
            label.push_back(row["tag"]);
            label_set.insert(row["tag"]);
            set<string> uniq = unique_words(row["content"]);
            all_post.push_back(uniq);
            for (set<string>::iterator it = uniq.begin();
            it != uniq.end(); it++) {
                string wd = *it;
                word_set.insert(wd);
            }
        }
        voc_size = word_set.size();
    }
    

    void calc_word_num() {
        for (set<string> pst : all_post) {
            set<string>::iterator si;
            for (si = pst.begin();si!=pst.end(); si++) {
                string wd = *si;
                post_word[wd] += 1;
            }
        }
    }

    void calc_label_num() {
        set<string>::iterator si;
        for (si = label_set.begin(); si!=label_set.end(); si++) {
            int count = 0;
            string lbl = *si;
            for (string i : label) {
                if (i == lbl) {
                    count++;
                }
            }
            post_label[lbl] = count;
        }
    }

    void calc_word_label_num() {
        int n = get_size();
        for (int i = 0; i < n; i++) {
            set<string> pst = all_post[i];
            string lbl = label[i];
            set<string>::iterator si;
            for (si = pst.begin();si!=pst.end(); si++) {
                string wd = *si;
                pair<string, string> pr;
                pr.first = lbl;
                pr.second = wd;
                post_word_label[pr] += 1;
            }
        }
    }

    void train() {
        calc_word_num();
        calc_label_num();
        calc_word_label_num();
    }

    void calc_log_prob(Classifier& train, vector<map<string, double>>& prob_vec) {
        int n = get_size();
        int tn = train.get_size();
        for (int i = 0; i < n; i++) {
            map<string, double> prob_map;
            for (set<string>::iterator iter = label_set.begin();
             iter!=label_set.end(); iter++) {
                double prob = 0;
                string lbl = *iter;
                prob += log(1.0*train.post_label[lbl]/tn);
                set<string> post = all_post[i];
                for (set<string>::iterator it = post.begin(); it!=post.end(); it++) {
                    string wd = *it;
                    calc_log_sup(train, wd, lbl, prob);
                }
                prob_map[lbl]=prob;
            }
            prob_vec.push_back(prob_map);
        }
    }

    void calc_log_sup(Classifier& train, string wd, string lbl, double& prob) {
        pair<string, string> pr;
        int tn = train.get_size();
        pr.first = lbl;
        pr.second = wd;
        int c = train.post_word_label[pr];
        if (c > 0) {
            prob += log(1.0*c/train.post_label[lbl]);
        } else {
            int cc = train.post_word[wd];
            if (cc > 0) {
                prob += log(1.0*cc/tn);
            } else {
                prob += log(1.0/tn);
            }
        }
    }

    void train_print() {
        cout << "training data:" << endl;
        int n = get_size();
        for (int i = 0; i < n; i++) {
            string lbl = label[i];
            string pst = post[i];
            cout << "  label = " << lbl << ", content = " << pst << endl;
        }
    }
    void print_lbl() {
        cout << "classes:" << endl;
        for (set<string>::iterator si = label_set.begin();
        si!=label_set.end(); si++) {
            string lbl = *si;
            cout << "  " << lbl << ", " << post_label[lbl]
            << " examples, log-prior = " << log(1.0*post_label[lbl]/size) << endl;
        }
        cout << "classifier parameters:" << endl;
        for (map<pair<string,string>, int>::iterator si = post_word_label.begin();
        si!=post_word_label.end(); si++) {
            pair<string,string> key = si->first;
            int value = si->second;
            if (value!=0) {
                cout << "  " << key.first << ":" << key.second << ", count = " 
                << value << ", log-likelihood = " 
                << log(1.0*value/post_label[key.first]) << endl;
            }
        }
        cout << endl;
    }
    void test_print(vector<pair<string, double>>& prob_vec) {
        cout << "test data:" << endl;
        int n = get_size();
        int cc = 0;
        for (int i = 0; i < n; i++) {
            cout << "  correct = " << label[i] << ", predicted = " << prob_vec[i].first
            << ", log-probability score = " << prob_vec[i].second << endl;
            cout << "  content = " << post[i] << endl;
            if (label[i]==prob_vec[i].first) {
                cc++;
            }
        }
        cout << "performance: " << cc << " / " << n 
        << " posts predicted correctly" << endl;
    }
};

vector<pair<string, double>> predict(vector<map<string, double>>& prob_vec, int size) {
    vector<pair<string, double>> pred;
    for (int i = 0; i < size; i++) {
        map<string, double> prob_map = prob_vec[i];
        pair<string, double> pr = *std::max_element(prob_map.begin(), prob_map.end(), 
        [] (const pair<string, double> & p1, const pair<string, double> & p2) {
        return p1.second < p2.second;});
        pred.push_back(pr);
    }
    return pred;
}

void print_result(Classifier train, Classifier test,
    vector<pair<string, double>>& prob_vec, string debug) {
    if (debug == "--debug") {
        train.train_print();
    }
    cout << "trained on " << train.get_size() << " examples" << endl;
    if (debug == "--debug") {
        cout << "vocabulary size = " << train.get_voc_size() << endl;
        cout << endl;
        train.print_lbl();
    }
    test.test_print(prob_vec);
}

int main(int argc, char* argv[]) {
    cout.precision(3);
    ifstream train, test;
    train.open(argv[1]);
    test.open(argv[2]);
    if (!train.is_open()) {
        cout << "Error opening file:" << argv[1] <<endl;
        return 1;
    }
    if (!test.is_open()) {
        cout << "Error opening file:" << argv[2] <<endl;
        return 1;
    }
    string debug;
    if (argv[3]) debug = argv[3];
    else debug = "";
    if ((argc!=3 && argc!=4) || (argc==4&&debug!="--debug")) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }
    csvstream tr(argv[1]);
    Classifier train_data;
    train_data.get_data(tr);
    train_data.train();
    csvstream ts(argv[2]);
    Classifier test_data;
    test_data.get_data(ts);
    vector<map<string, double>> test_prob;
    test_data.calc_log_prob(train_data, test_prob);
    vector<pair<string, double>> pred = predict(test_prob, test_data.get_size());
    print_result(train_data, test_data, pred, debug);
}