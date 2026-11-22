import csv
import unittest
from pathlib import Path

DATA = Path(__file__).resolve().parents[1] / "data" / "sample_slots.csv"
EXPECTED = ["timestamp", "slot1_occupied", "slot2_occupied", "slot3_occupied", "slot4_occupied"]

class SampleParkingDataTests(unittest.TestCase):
    def test_schema_and_nonempty_rows(self):
        with DATA.open(newline="", encoding="utf-8") as handle:
            reader = csv.DictReader(handle)
            self.assertEqual(reader.fieldnames, EXPECTED)
            rows = list(reader)
        self.assertGreater(len(rows), 0)

    def test_occupancy_values_are_binary_and_four_slots(self):
        with DATA.open(newline="", encoding="utf-8") as handle:
            rows = list(csv.DictReader(handle))
        for row in rows:
            values = [row[f"slot{i}_occupied"] for i in range(1, 5)]
            self.assertEqual(len(values), 4)
            self.assertTrue(all(value in {"0", "1"} for value in values))

if __name__ == "__main__":
    unittest.main()
