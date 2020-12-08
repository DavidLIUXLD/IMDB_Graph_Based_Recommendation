
//
// Created by Dillan Maraj on 12/6/20.
//

#ifndef IMDB_GRAPH_BASED_RECOMMENDATION_FILEREADER_H
#define IMDB_GRAPH_BASED_RECOMMENDATION_FILEREADER_H
void read_Meta(unordered_map<int, string> &filmCollection, unordered_map<int, vector<int>> &genreCollection);
void read_Keywords(unordered_map<int, vector<int>> keywordCollection);

#endif //IMDB_GRAPH_BASED_RECOMMENDATION_FILEREADER_H
