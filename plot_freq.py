import matplotlib.pyplot as plt
import sys

def read_mycsv(lines):
    is_first = True
    times = []
    for line in lines:
        if is_first:
            cores = line.split(", ")[1:]
            is_first = False
            freqs = [[] for x in range(len(cores))]
        else:
            data = line.split(", ")
            times.append(float(data[0]))
            freq = data[1:]
            for i in range(len(freq)):
                freqs[i].append(int(freq[i]))
    return cores, times, freqs


def plot_freqs(cores, times, freqs):
    plts = []
    for i in range(len(freqs)):
        plts.append(plt.plot(times, freqs[i]))
    plt.legend(map(lambda x: x[0], plts), (x for x in cores), loc=2)


def main(file, until=0.0, until_line=0):
    f = open(file)
    lines = f.readlines()
    cores, times, freqs = read_mycsv(lines)
    plot_freqs(cores, times, freqs)
    plt.show()
    if until != 0.0:
        for i in range(len(times)):
            if times[i] > until:
                until_line = i
                break
    if until_line != 0:
        flat_freqs = []
        for i in range(len(cores)):
            flat_freqs = flat_freqs + freqs[i][:until_line]
        print "ave: %s" % (sum(flat_freqs)/len(flat_freqs))
        print "until_line: %s" % until_line

if __name__ == "__main__":
    if len(sys.argv) == 2:
        main(sys.argv[1])
    elif len(sys.argv) == 3:
        main(sys.argv[1], float(sys.argv[2]))
    elif len(sys.argv) == 4:
        main(sys.argv[1], 0.0, int(sys.argv[3]))
    else:
        print "please input the file name as arg."
