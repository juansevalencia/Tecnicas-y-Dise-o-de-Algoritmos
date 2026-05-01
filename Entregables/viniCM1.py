import heapq

def dijkstra(n, k, travel_times, elevator_floors):
    INF = float('inf')
    dist = {}
    pq = []

    elevator_floors_sets = [set(floors) for floors in elevator_floors]
    floor_elevators = {}
    for asc, floors in enumerate(elevator_floors):
        for piso in floors:
            if piso not in floor_elevators:
                floor_elevators[piso] = []
            floor_elevators[piso].append(asc)

    for i in range(n):
        if 0 in elevator_floors_sets[i]:
            pq.append((0, 0, i))
            dist[(0, i)] = 0

    while pq:
        tiempo, piso, asc = heapq.heappop(pq)

        if piso == k:
            return tiempo

        if tiempo > dist.get((piso, asc), INF):
            continue

        if piso in elevator_floors_sets[asc]:
            for siguiente_piso in elevator_floors[asc]:
                if siguiente_piso != piso:
                    siguiente_tiempo = tiempo + travel_times[asc] * abs(siguiente_piso - piso)
                    if siguiente_tiempo < dist.get((siguiente_piso, asc), INF):
                        dist[(siguiente_piso, asc)] = siguiente_tiempo
                        heapq.heappush(pq, (siguiente_tiempo, siguiente_piso, asc))

        for nuevo_asc in floor_elevators[piso]:
            if nuevo_asc != asc:
                tiempo_cambio = tiempo + 60
                if tiempo_cambio < dist.get((piso, nuevo_asc), INF):
                    dist[(piso, nuevo_asc)] = tiempo_cambio
                    heapq.heappush(pq, (tiempo_cambio, piso, nuevo_asc))

    return 'IMPOSSIBLE'
def main():
    res = []
    while True:
        try:
            algo= input().split()
            if not algo:
                break
            n, k = map(int, algo)
            t = list(map(int, input().split()))
            floors = [list(map(int, input().split())) for _ in range(n)]
            resultado = dijkstra(n, k, t, floors)
            res.append(resultado)
        except EOFError:
            break
    print("\n".join(str(x) for x in res))

if __name__ == "__main__":
    main()