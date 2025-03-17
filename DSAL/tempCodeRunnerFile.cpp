  void DFS(int v1, bool visited[])
    {
        Node *temp = head[v1];
        cout << v1 << " ";
        visited[v1] = true;
        while (temp != nullptr)
        {
            if (!visited[temp->getData()])
            {
                DFS(temp->getData(), visited);
            }
            temp = temp->getNext();
        }
    }