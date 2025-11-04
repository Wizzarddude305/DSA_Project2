#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMessageBox>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

#include "pokemon.h"
#include "hashTable.h"
#include "trieTree.h"

using namespace std;

static vector<string> splitByComma(const string &line) {
    vector<string> parts;
    size_t start = 0, end = 0;
    while ((end = line.find(',', start)) != string::npos) {
        parts.push_back(line.substr(start, end - start));
        start = end + 1;
    }
    // last segment
    parts.push_back(line.substr(start));
    return parts;
}

static string trim(const string &s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

static vector<Pokemon> loadPokemonsFromFile(const string &fileName) {
    ifstream infile(fileName);
    vector<Pokemon> pokemons;
    if (!infile) {
        return pokemons;
    }
    string line;
    int lineNumber = 0;
    Pokemon pokemon;
    while (getline(infile, line)) {
        size_t end = 0;
        vector<string> data;
        if (lineNumber % 3 == 0) {
            if (lineNumber != 0) {
                pokemons.push_back(pokemon);
                pokemon.empty();
            }
            auto parts = splitByComma(line);
            if (parts.size() >= 3) {
                string name = trim(parts[0]);
                string genNum = parts[1];
                end = genNum.find(':');
                int genNumI = end != string::npos ? stoi(genNum.substr(end + 1)) : -1;
                string rank = parts[2];
                end = rank.find(':');
                int rankI = end != string::npos ? stoi(rank.substr(end + 1)) : -1;
                pokemon.setName(name);
                pokemon.setRank(rankI);
                pokemon.setGen(genNumI);
            }
        } else if (lineNumber % 3 == 1) {
            map<string, float> moveStats;
            size_t pos = 0, next;
            while ((next = line.find(',', pos)) != string::npos) {
                string token = line.substr(pos, next - pos);
                size_t colon = token.find(':');
                if (colon != string::npos) {
                    string moveName = trim(token.substr(0, colon));
                    string perc = trim(token.substr(colon + 1));
                    // strip trailing % if present
                    if (!perc.empty() && perc.back() == '%') perc.pop_back();
                    try { moveStats[moveName] = stof(perc); } catch (...) {}
                }
                pos = next + 1;
            }
            // handle last token (no trailing comma)
            if (pos < line.size()) {
                string token = line.substr(pos);
                size_t colon = token.find(':');
                if (colon != string::npos) {
                    string moveName = trim(token.substr(0, colon));
                    string perc = trim(token.substr(colon + 1));
                    if (!perc.empty() && perc.back() == '%') perc.pop_back();
                    try { moveStats[moveName] = stof(perc); } catch (...) {}
                }
            }
            pokemon.setMoveStats(moveStats);
        } else if (lineNumber % 3 == 2) {
            map<string, float> teamStats;
            size_t pos = 0, next;
            while ((next = line.find(',', pos)) != string::npos) {
                string token = line.substr(pos, next - pos);
                size_t colon = token.find(':');
                if (colon != string::npos) {
                    string teamName = trim(token.substr(0, colon));
                    string perc = trim(token.substr(colon + 1));
                    if (!perc.empty() && perc.back() == '%') perc.pop_back();
                    try { teamStats[teamName] = stof(perc); } catch (...) {}
                }
                pos = next + 1;
            }
            if (pos < line.size()) {
                string token = line.substr(pos);
                size_t colon = token.find(':');
                if (colon != string::npos) {
                    string teamName = trim(token.substr(0, colon));
                    string perc = trim(token.substr(colon + 1));
                    if (!perc.empty() && perc.back() == '%') perc.pop_back();
                    try { teamStats[teamName] = stof(perc); } catch (...) {}
                }
            }
            pokemon.setTeamStats(teamStats);
        }
        lineNumber++;
    }
    infile.close();
    return pokemons;
}

class MainWindow : public QMainWindow {
    Q_OBJECT // Q_OBJECT requires including the generated MOC at end of this file
public:
    explicit MainWindow(QWidget *parent = nullptr)
            : QMainWindow(parent) {
        setWindowTitle("Pokemon Search");

        QWidget *central = new QWidget(this);
        QVBoxLayout *root = new QVBoxLayout(central);

        QHBoxLayout *row1 = new QHBoxLayout();
        dsCombo = new QComboBox(this);
        dsCombo->addItem("HashTable", QVariant("hash"));
        dsCombo->addItem("Trie", QVariant("trie"));
        statCombo = new QComboBox(this);
        statCombo->addItem("Teammates", QVariant("team"));
        statCombo->addItem("Moves", QVariant("move"));
        nameEdit = new QLineEdit(this);
        nameEdit->setPlaceholderText("Enter Pokemon name (e.g., Excadrill)");
        QPushButton *searchBtn = new QPushButton("Search", this);
        row1->addWidget(new QLabel("Data structure:"));
        row1->addWidget(dsCombo);
        row1->addSpacing(12);
        row1->addWidget(new QLabel("Statistic:"));
        row1->addWidget(statCombo);
        row1->addSpacing(12);
        row1->addWidget(nameEdit, 1);
        row1->addWidget(searchBtn);

        statusLabel = new QLabel("Ready", this);
        table = new QTableWidget(this);
        table->setColumnCount(2);
        QStringList headers;
        headers << "Item" << "Percent";
        table->setHorizontalHeaderLabels(headers);
        table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        table->verticalHeader()->setVisible(false);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        root->addLayout(row1);
        root->addWidget(statusLabel);
        root->addWidget(table, 1);
        setCentralWidget(central);

        connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearch);

        // Load data and build structures
        statusLabel->setText("Loading data...");
        QApplication::processEvents();
        pokemons = loadPokemonsFromFile("data/cppOrganized/AllPokemon-organized.txt");
        for (auto &p : pokemons) {
            tableHash.insert(p);
            trie.insert(p);
        }
        statusLabel->setText(QString("Loaded %1 Pokemon").arg(static_cast<int>(pokemons.size())));
    }

private Q_SLOTS: // QT_NO_KEYWORDS set in CMake: use Q_SLOTS instead of 'slots'
    void onSearch() {
        QString nameQ = nameEdit->text().trimmed();
        if (nameQ.isEmpty()) {
            QMessageBox::information(this, "Info", "Please enter a Pokemon name.");
            return;
        }
        string name = nameQ.toStdString();
        // Case-insensitive: convert to lower for Trie internals, but our DS already handles tolower internally

        string ds = dsCombo->currentData().toString().toStdString();
        string stat = statCombo->currentData().toString().toStdString();

        bool found = false;
        Pokemon p;
        if (ds == "hash") {
            found = tableHash.search(name);
            if (found) p = tableHash.get(name);
        } else {
            found = trie.search(name);
            if (found) p = trie.get(name);
        }

        if (!found) {
            statusLabel->setText("Not found");
            table->setRowCount(0);
            return;
        }

        // Populate table with chosen stats
        vector<pair<string, float>> rows;
        if (stat == "team") {
            for (auto &kv : p.getTeamStats()) rows.push_back(kv);
        } else {
            for (auto &kv : p.getMoveStats()) rows.push_back(kv);
        }
        sort(rows.begin(), rows.end(), [](const auto &a, const auto &b){ return a.second > b.second; });

        table->setRowCount(static_cast<int>(rows.size()));
        for (int i = 0; i < static_cast<int>(rows.size()); ++i) {
            auto *item0 = new QTableWidgetItem(QString::fromStdString(rows[i].first));
            auto *item1 = new QTableWidgetItem(QString::number(rows[i].second, 'f', 2) + "%");
            table->setItem(i, 0, item0);
            table->setItem(i, 1, item1);
        }
        statusLabel->setText(QString("%1 | Gen %2 | Rank %3 | %4 entries")
                                     .arg(QString::fromStdString(p.getName()))
                                     .arg(p.getGen())
                                     .arg(p.getRank())
                                     .arg(table->rowCount()));
    }

private:
    QLineEdit *nameEdit{};
    QComboBox *dsCombo{};
    QComboBox *statCombo{};
    QLabel *statusLabel{};
    QTableWidget *table{};

    vector<Pokemon> pokemons;
    HashTable tableHash;
    TrieTree trie;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.resize(800, 600);
    w.show();
    return app.exec();
}

#include "app_ui.moc"



