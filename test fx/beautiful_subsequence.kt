import java.util.*
import java.io.*

class FastReader(`in`: InputStream) {
    private val reader: BufferedReader = BufferedReader(InputStreamReader(`in`))
    private var tokenizer: StringTokenizer? = null

    operator fun next(): String? {
        while (tokenizer == null || !tokenizer!!.hasMoreElements()) {
            val line = reader.readLine() ?: return null
            tokenizer = StringTokenizer(line)
        }
        return tokenizer!!.nextToken()
    }

    fun nextInt(): Int = next()!!.toInt()
    fun nextLong(): Long = next()!!.toLong()
}

fun solve() {
    val fr = FastReader(System.`in`)
    val out = PrintWriter(System.out)

    val nextN = fr.next() ?: return
    val n = nextN.toInt()
    val q = fr.nextInt()

    val a = LongArray(n) { fr.nextLong() }
    val p = LongArray(n)
    
    p[0] = 1L
    for (i in 0 until n - 1) {
        val dist = if (a[i] == a[i + 1]) 2L else Math.abs(a[i + 1] - a[i])
        p[i + 1] = p[i] + dist
    }

    val results = LongArray(q)
    for (i in 0 until q) {
        val x = fr.nextLong()
        if (x > p[n - 1]) {
            results[i] = -1L
        } else {
            var res = Arrays.binarySearch(p, x)
            if (res >= 0) {
                results[i] = a[res]
            } else {
                val ins = -res - 1
                val segStartIdx = ins - 1
                val segEndIdx = ins
                
                if (a[segStartIdx] == a[segEndIdx]) {
                    results[i] = 0L
                } else {
                    val startVal = a[segStartIdx]
                    val endVal = a[segEndIdx]
                    val posInSeg = x - p[segStartIdx]
                    if (endVal > startVal) {
                        results[i] = startVal + posInSeg
                    } else {
                        results[i] = startVal - posInSeg
                    }
                }
            }
        }
    }

    out.println(results.joinToString(" "))
    out.flush()
}

fun main() {
    solve()
}
